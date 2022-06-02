#include "BurgerTimePCH.h"
#include "EnemyDiedCommand.h"

#include "EnemyComponent.h"

EnemyDiedCommand::EnemyDiedCommand(GameObject* pGameObject)
	: BaseCommand(pGameObject)
	, m_pEnemyComp{ nullptr }
{
	m_pEnemyComp = pGameObject->GetComponent<EnemyComponent>();
}

void EnemyDiedCommand::Execute()
{
	if (m_pEnemyComp)
	{
		m_pEnemyComp->Died();
	}
}