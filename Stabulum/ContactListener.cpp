#include "StabulumPCH.h"
#include "ContactListener.h"

#include "b2_contact.h"
#include "BoxColliderComponent.h"

void ContactListener::BeginContact(b2Contact* contact)
{
	BoxColliderComponent* pContact1 = reinterpret_cast<BoxColliderComponent*>(contact->GetFixtureA()->GetUserData().pointer);
	BoxColliderComponent* pContact2 = reinterpret_cast<BoxColliderComponent*>(contact->GetFixtureB()->GetUserData().pointer);

	Contact temp{ Contact::Type::OnCollisionBegin };

	if (pContact1->GetIsSensor() || pContact2->GetIsSensor())
	{
		temp.Type = Contact::Type::OnSensorBegin;
	}

	m_Contacts.push_back(Contact{ temp.Type, pContact1, pContact2 });
}

void ContactListener::EndContact(b2Contact* contact)
{
	BoxColliderComponent* pContact1 = reinterpret_cast<BoxColliderComponent*>(contact->GetFixtureA()->GetUserData().pointer);
	BoxColliderComponent* pContact2 = reinterpret_cast<BoxColliderComponent*>(contact->GetFixtureB()->GetUserData().pointer);

	Contact temp{ Contact::Type::OnCollisionEnd };

	if (pContact1->GetIsSensor() || pContact2->GetIsSensor())
	{
		temp.Type = Contact::Type::OnSensorEnd;
	}

	m_Contacts.push_back(Contact{ temp.Type, pContact1, pContact2 });
}