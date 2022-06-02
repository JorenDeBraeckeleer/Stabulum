#include "BurgerTimePCH.h"
#include "BurgerComponent.h"

void BurgerComponent::Update()
{
}

void BurgerComponent::Dropped()
{
	Notify(m_pGameObject, GameEvent::BurgerDropped);
}