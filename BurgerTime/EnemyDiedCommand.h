#pragma once
#include "BaseCommand.h"

class EnemyComponent;

class EnemyDiedCommand final : public BaseCommand
{
public:
	EnemyDiedCommand(GameObject* pGameObject);
	virtual ~EnemyDiedCommand() = default;

	virtual void Execute() override;

private:
	EnemyComponent* m_pEnemyComp;
};