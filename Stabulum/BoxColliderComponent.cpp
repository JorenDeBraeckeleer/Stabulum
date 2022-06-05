#include "StabulumPCH.h"
#include "BoxColliderComponent.h"

//#include "b2_fixture.h"

#include "WorldComponent.h"

BoxColliderComponent::BoxColliderComponent(RigidBodyComponent* pRigidBodyComponent, float width, float height, float centerX, float centerY, float angle, int groupIndex)
	: ColliderComponent()
	, m_pRigidBodyComponent{ pRigidBodyComponent }
	, m_Width{ width }
	, m_Height{ height }
	, m_CenterX{ centerX }
	, m_CenterY{ centerY }
	, m_Angle{ angle }
	, m_GroupIndex{ groupIndex }
{
}

void BoxColliderComponent::Update()
{
	if (m_IsUpdateNeeded)
	{
		if (GameObject* pParent = GetGameObject()->GetParent())
		{
			pParent->GetComponentInParents<WorldComponent>()->AddToBodyColliderBox(m_pRigidBodyComponent, this, int16(m_GroupIndex));

			m_IsUpdateNeeded = false;
		}
	}
}