#include "BurgerTimePCH.h"
#include "LoseLifeCommand.h"

#include "PeterPepperComponent.h"

LoseLifeCommand::LoseLifeCommand(GameObject* pGameObject)
	: BaseCommand(pGameObject)
	, m_pPeterPepperComp{ nullptr }
{
	m_pPeterPepperComp = m_pGameObject->GetComponent<PeterPepperComponent>();
}

void LoseLifeCommand::Execute()
{
	if (m_pPeterPepperComp)
	{
		m_pPeterPepperComp->LostLife();
	}
}