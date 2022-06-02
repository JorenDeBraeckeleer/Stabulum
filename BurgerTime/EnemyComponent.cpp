#include "BurgerTimePCH.h"
#include "EnemyComponent.h"

void EnemyComponent::Update()
{
}

void EnemyComponent::Died()
{
	Notify(m_pGameObject, GameEvent::EnemyDied);
}