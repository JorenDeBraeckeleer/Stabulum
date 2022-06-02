#pragma once

#include "b2_world.h"

class BoxColliderComponent;

class ContactListener final : public b2ContactListener
{
public:
	ContactListener() = default;

	struct Contact
	{
		enum class Type
		{
			OnSensorBegin,
			OnSensorEnd,
			OnCollisionBegin,
			OnCollisionEnd,
		};

		Type Type;
		BoxColliderComponent* pContact1;
		BoxColliderComponent* pContact2;
	};

	virtual void BeginContact(b2Contact* contact) override;
	virtual void EndContact(b2Contact* contact) override;

	std::vector<Contact> GetContacts() { return m_Contacts; }
	void ResetContacts() { m_Contacts.clear(); }

private:
	std::vector<Contact> m_Contacts;
};