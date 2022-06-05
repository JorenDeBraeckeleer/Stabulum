#include "StabulumPCH.h"
#include "CircleColliderComponent.h"

#include "WorldComponent.h"

CircleColliderComponent::CircleColliderComponent(RigidBodyComponent* pRigidBodyComponent, float radius, FVec2 point, int groupIndex)
	: ColliderComponent()
	, m_pRigidBodyComponent{ pRigidBodyComponent }
	, m_Radius{ radius }
	, m_Point{ point }
	, m_GroupIndex{ groupIndex }
{
}

void CircleColliderComponent::Update()
{
	if (m_IsUpdateNeeded)
	{
		if (GameObject* pParent = GetGameObject()->GetParent())
		{
			pParent->GetComponent<WorldComponent>()->AddToBodyColliderCircle(m_pRigidBodyComponent, this, int16(m_GroupIndex));

			m_IsUpdateNeeded = false;
		}
	}
}