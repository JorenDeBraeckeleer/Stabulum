#pragma once
#include "BaseCommand.h"

class MovementComponent;

class MoveCommand : public BaseCommand
{
public:
	MoveCommand(GameObject* pGameObject);
	virtual ~MoveCommand() = default;

	virtual void Execute() = 0;

protected:
	MovementComponent* m_pMovementComp;
};

class MoveUpCommand final : public MoveCommand
{
public:
	MoveUpCommand(GameObject* pGameObject);
	virtual ~MoveUpCommand() = default;

	virtual void Execute() override;
};

class MoveDownCommand final : public MoveCommand
{
public:
	MoveDownCommand(GameObject* pGameObject);
	virtual ~MoveDownCommand() = default;

	virtual void Execute() override;
};

class MoveLeftCommand final : public MoveCommand
{
public:
	MoveLeftCommand(GameObject* pGameObject);
	virtual ~MoveLeftCommand() = default;

	virtual void Execute() override;
};

class MoveRightCommand final : public MoveCommand
{
public:
	MoveRightCommand(GameObject* pGameObject);
	virtual ~MoveRightCommand() = default;

	virtual void Execute() override;
};