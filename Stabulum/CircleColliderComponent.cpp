#include "StabulumPCH.h"
#include "CircleColliderComponent.h"

#include "WorldComponent.h"

CircleColliderComponent::CircleColliderComponent(RigidBodyComponent* pRigidBodyComponent, float radius, FVec2 point)
	: ColliderComponent()
	, m_pRigidBodyComponent{ pRigidBodyComponent }
	, m_Radius{ radius }
	, m_Point{ point }
{
}

void CircleColliderComponent::Update()
{
	if (m_IsUpdateNeeded)
	{
		if (GameObject* pParent = GetGameObject()->GetParent())
		{
			pParent->GetComponent<WorldComponent>()->AddToBodyColliderCircle(m_pRigidBodyComponent, this);

			m_IsUpdateNeeded = false;
		}
	}
}