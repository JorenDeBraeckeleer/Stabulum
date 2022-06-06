#include "StabulumPCH.h"
#include "RigidBodyComponent.h"

#include "b2_body.h"

#include "TransformComponent.h"
#include "WorldComponent.h"

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
	, m_NewPosition{}
	, m_ChangeTransform{}
	, m_IsUpdateNeeded{ true }
{
}

void RigidBodyComponent::FixedUpdate()
{
	if (m_ChangeTransform)
	{
		m_pPhysicsBody->SetTransform({m_NewPosition.x, m_NewPosition.y }, 0.f);

		m_NewPosition = { 0.f, 0.f };

		m_ChangeTransform = false;
	}
}

void RigidBodyComponent::Update()
{
	if (m_IsUpdateNeeded)
	{
		if (GameObject* pParent = GetGameObject()->GetParent())
		{
			pParent->GetComponentInParents<WorldComponent>()->AddBody(m_pTransformComponent, this);

			m_IsUpdateNeeded = false;
		}
	}
}

void RigidBodyComponent::UpdatePosition()
{
	m_pTransformComponent->SetWorldPosition(m_pPhysicsBody->GetPosition().x, m_pPhysicsBody->GetPosition().y, false);

	//Update childrens position
	for (GameObject* pChild : GetGameObject()->GetChildren())
	{
		if (RigidBodyComponent* pComp = pChild->GetComponent<RigidBodyComponent>())
		{
			pComp->SetPosition(pChild->GetComponent<TransformComponent>()->GetWorldPosition(false));
		}
	}
}

void RigidBodyComponent::SetBodyLinearVelocity(float velocityX, float velocityY)
{
	m_pPhysicsBody->SetLinearVelocity(b2Vec2{ velocityX, velocityY });
}

void RigidBodyComponent::AddBodyForce(const FVec2& force)
{
	m_pPhysicsBody->ApplyForce(b2Vec2{ force.x, force.y }, m_pPhysicsBody->GetWorldCenter(), true);
}

void RigidBodyComponent::UpdateGravityScale(float scale)
{
	SetGravityScale(scale);
	m_pPhysicsBody->SetAwake(true);
	m_pPhysicsBody->SetGravityScale(m_GravityScale);
}

void RigidBodyComponent::SetPosition(const FVec2& position)
{
	m_ChangeTransform = true;
	m_NewPosition = m_NewPosition + position;
}