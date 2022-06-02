#include "StabulumPCH.h"
#include "RigidBodyComponent.h"

#include "WorldComponent.h"
#include "TransformComponent.h"

#include "b2_body.h"

RigidBodyComponent::RigidBodyComponent(TransformComponent* pTransformComponent, BodyType bodyType, float angle, float gravityScale, bool hasFixedRotation)
	: BaseComponent()
	, m_pTransformComponent{ pTransformComponent }
	, m_LinearVelocity{ 0.f, 0.f }
	, m_Angle{ angle }
	, m_AngularVelocity{ 0.f }
	, m_LinearDamping{ 0.f }
	, m_AngularDamping{ 0.f }
	, m_GravityScale{ gravityScale }
	, m_AllowSleep{ true }
	, m_IsAwake{ true }
	, m_HasFixedRotation{ hasFixedRotation }
	, m_IsBullet{ false }
	, m_IsEnabled{ true }
	, m_BodyType{ bodyType }
	, m_pPhysicsBody{}
	, m_IsUpdateNeeded{ true }
{
}

void RigidBodyComponent::Update()
{
	if (m_IsUpdateNeeded)
	{
		if (GameObject* pParent = GetGameObject()->GetParent())
		{
			pParent->GetComponent<WorldComponent>()->AddBody(m_pTransformComponent, this);

			m_IsUpdateNeeded = false;
		}
	}
}

void RigidBodyComponent::UpdatePosition()
{
	m_pTransformComponent->SetPosition(m_pPhysicsBody->GetPosition().x, m_pPhysicsBody->GetPosition().y);
	//std::cout << m_pPhysicsBody->GetPosition().x << ", " << m_pPhysicsBody->GetPosition().y << std::endl;
}

void RigidBodyComponent::UpdateLinearVelocity(float velocityX, float velocityY)
{
	m_pPhysicsBody->SetLinearVelocity(b2Vec2{ velocityX, velocityY });
}