#include "StabulumPCH.h"
#include "BoxColliderComponent.h"

#include "b2_fixture.h"

#include "WorldComponent.h"

BoxColliderComponent::BoxColliderComponent(RigidBodyComponent* pRigidBodyComponent, float width, float height, float centerX, float centerY, float angle)
	: ColliderComponent()
	, m_pRigidBodyComponent{ pRigidBodyComponent }
	, m_Width{ width }
	, m_Height{ height }
	, m_CenterX{ centerX }
	, m_CenterY{ centerY }
	, m_Angle{ angle }
	, m_IsSensor{ false }
	, m_Friction{ 0.2f }
	, m_Restitution{ 0.f }
	, m_RestitutionTreshold{ 1.f }
	, m_Density{ 0.f }
	, m_pPhysicsFixture{}
	, m_IsUpdateNeeded{ true }
{
}

void BoxColliderComponent::Update()
{
	if (m_IsUpdateNeeded)
	{
		if (GameObject* pParent = GetGameObject()->GetParent())
		{
			pParent->GetComponent<WorldComponent>()->AddToBodyColliderBox(m_pRigidBodyComponent, this);

			m_IsUpdateNeeded = false;
		}
	}
}