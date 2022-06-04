#include "BurgerTimePCH.h"
#include "BurgerPartComponent.h"

#include "TransformComponent.h"
#include "ColliderComponent.h"
#include "BoxColliderComponent.h"
#include "RigidBodyComponent.h"

BurgerPartComponent::BurgerPartComponent()
	: m_IsHit{ false }
{
}

void BurgerPartComponent::Update()
{
}

void BurgerPartComponent::OnTriggerEnter(ColliderComponent*)
{
	if (!m_IsHit)
	{
		FVec2 pos = GetGameObject()->GetComponent<TransformComponent>()->GetUnitPosition();
		RigidBodyComponent* pBodyComp = GetGameObject()->GetComponent<RigidBodyComponent>();
		pBodyComp->SetPosition({ pos.x, pos.y + 0.125f });

		m_IsHit = true;
	}
}