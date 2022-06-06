#include "BurgerTimePCH.h"
#include "BurgerPlatformComponent.h"

#include "BurgerComponent.h"
#include "ColliderComponent.h"
#include "RigidBodyComponent.h"
#include "ServiceLocator.h"

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
	ServiceLocator::GetSoundManager()->Play(2, 5, false);

	BurgerComponent* pBurgerComp = pCollider->GetGameObject()->GetComponent<BurgerComponent>();
	pBurgerComp->Dropped();
}