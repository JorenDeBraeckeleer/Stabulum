#include "BurgerTimePCH.h"
#include "BurgerDroppedCommand.h"

#include "BurgerComponent.h"

BurgerDroppedCommand::BurgerDroppedCommand(GameObject* pGameObject)
	: BaseCommand(pGameObject)
	, m_pBurgerComp{ nullptr }
{
	m_pBurgerComp = pGameObject->GetComponent<BurgerComponent>();
}

void BurgerDroppedCommand::Execute()
{
	if (m_pBurgerComp)
	{
		m_pBurgerComp->Dropped();
	}
}