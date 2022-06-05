#include "BurgerTimePCH.h"
#include "BurgerPlatformComponent.h"

#include "ColliderComponent.h"
#include "RigidBodyComponent.h"
#include "BurgerComponent.h"

void BurgerPlatformComponent::Update()
{
}

void BurgerPlatformComponent::OnTriggerEnter(ColliderComponent* pCollider)
{
	RigidBodyComponent* pBodyComp = pCollider->GetGameObject()->GetComponent<RigidBodyComponent>();
	pBodyComp->UpdateGravityScale(0.f);
	pBodyComp->SetBodyLinearVelocity(0.f, 0.f);
}

void BurgerPlatformComponent::OnTriggerExit(ColliderComponent* pCollider)
{
	RigidBodyComponent* pBodyComp = pCollider->GetGameObject()->GetComponent<RigidBodyComponent>();
	pBodyComp->UpdateGravityScale(1.f);
	BurgerComponent* pBurgerComp = pCollider->GetGameObject()->GetComponent<BurgerComponent>();
	pBurgerComp->ResetParts();
}