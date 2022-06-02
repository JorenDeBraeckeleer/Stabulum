#pragma once
#include "BaseCommand.h"

class BurgerComponent;

class BurgerDroppedCommand final : public BaseCommand
{
public:
	BurgerDroppedCommand(GameObject* pGameObject);
	virtual ~BurgerDroppedCommand() = default;

	virtual void Execute() override;

private:
	BurgerComponent* m_pBurgerComp;
};