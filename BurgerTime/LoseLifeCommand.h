#pragma once
#include "BaseCommand.h"

class PeterPepperComponent;

class LoseLifeCommand final : public BaseCommand
{
public:
	LoseLifeCommand(GameObject* pGameObject);
	virtual ~LoseLifeCommand() = default;

	virtual void Execute() override;

private:
	PeterPepperComponent* m_pPeterPepperComp;
};