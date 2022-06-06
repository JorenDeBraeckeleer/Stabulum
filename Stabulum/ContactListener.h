#pragma once

#include "b2_world.h"

class ColliderComponent;

class ContactListener final : public b2ContactListener
{
public:
	ContactListener() = default;
	~ContactListener() = default;

	ContactListener(const ContactListener&) = delete;
	ContactListener(ContactListener&&) = delete;
	ContactListener& operator= (const ContactListener&) = delete;
	ContactListener& operator= (const ContactListener&&) = delete;

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
		ColliderComponent* pContact1;
		ColliderComponent* pContact2;
	};

	virtual void BeginContact(b2Contact* contact) override;
	virtual void EndContact(b2Contact* contact) override;

	std::vector<Contact> GetContacts() { return m_Contacts; }
	void ResetContacts() { m_Contacts.clear(); }

private:
	std::vector<Contact> m_Contacts;
};