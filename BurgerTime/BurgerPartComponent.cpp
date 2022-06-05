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
		RigidBodyComponent* pBodyComp = GetGameObject()->GetComponent<RigidBodyComponent>();
		pBodyComp->SetPosition({ 0.f, 0.125f });

		m_IsHit = true;
	}
}