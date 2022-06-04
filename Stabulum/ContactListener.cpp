#include "StabulumPCH.h"
#include "ContactListener.h"

#include "b2_contact.h"
#include "ColliderComponent.h"

void ContactListener::BeginContact(b2Contact* contact)
{
	ColliderComponent* pContact1 = reinterpret_cast<ColliderComponent*>(contact->GetFixtureA()->GetUserData().pointer);
	ColliderComponent* pContact2 = reinterpret_cast<ColliderComponent*>(contact->GetFixtureB()->GetUserData().pointer);

	Contact temp{ Contact::Type::OnCollisionBegin };

	if (pContact1->GetIsSensor() || pContact2->GetIsSensor())
	{
		temp.Type = Contact::Type::OnSensorBegin;
	}

	m_Contacts.emplace_back(Contact{ temp.Type, pContact1, pContact2 });

	if (pContact1->OnTriggerEnter != nullptr)
	{
		pContact1->OnTriggerEnter(pContact2);
	}
	if (pContact2->OnTriggerEnter != nullptr)
	{
		pContact2->OnTriggerEnter(pContact1);
	}
}

void ContactListener::EndContact(b2Contact* contact)
{
	ColliderComponent* pContact1 = reinterpret_cast<ColliderComponent*>(contact->GetFixtureA()->GetUserData().pointer);
	ColliderComponent* pContact2 = reinterpret_cast<ColliderComponent*>(contact->GetFixtureB()->GetUserData().pointer);

	Contact temp{ Contact::Type::OnCollisionEnd };

	if (pContact1->GetIsSensor() || pContact2->GetIsSensor())
	{
		temp.Type = Contact::Type::OnSensorEnd;
	}

	m_Contacts.emplace_back(Contact{ temp.Type, pContact1, pContact2 });
}