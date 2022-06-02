#pragma once
#include "GameObject.h"

class BaseCommand
{
public:
	virtual ~BaseCommand() = default;

	virtual void Execute() = 0;

protected:
	BaseCommand();
	BaseCommand(GameObject* pGameObject);

	GameObject* m_pGameObject;
};