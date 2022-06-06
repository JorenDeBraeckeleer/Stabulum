#include "BurgerTimePCH.h"
#include "MoveCommand.h"

#include "SceneManager.h"
#include "MovementComponent.h"

MoveCommand::MoveCommand(GameObject* pGameObject)
	: BaseCommand(pGameObject)
	, m_pMovementComp{ nullptr }
{
	m_pMovementComp = pGameObject->GetComponent<MovementComponent>();
}

MoveUpCommand::MoveUpCommand(GameObject* pGameObject)
	: MoveCommand(pGameObject)
{
}

void MoveUpCommand::Execute()
{
	if (m_pGameObject->GetScene() == SceneManager::GetInstance().GetActiveScene())
	{
		if (m_pMovementComp)
		{
			m_pMovementComp->SetMoveDirection(MovementComponent::MoveDirection::Up);
		}
	}
}

MoveDownCommand::MoveDownCommand(GameObject* pGameObject)
	: MoveCommand(pGameObject)
{
}

void MoveDownCommand::Execute()
{
	if (m_pGameObject->GetScene() == SceneManager::GetInstance().GetActiveScene())
	{
		if (m_pMovementComp)
		{
			m_pMovementComp->SetMoveDirection(MovementComponent::MoveDirection::Down);
		}
	}
}

MoveLeftCommand::MoveLeftCommand(GameObject* pGameObject)
	: MoveCommand(pGameObject)
{
}

void MoveLeftCommand::Execute()
{
	if (m_pGameObject->GetScene() == SceneManager::GetInstance().GetActiveScene())
	{
		if (m_pMovementComp)
		{
			m_pMovementComp->SetMoveDirection(MovementComponent::MoveDirection::Left);
		}
	}
}

MoveRightCommand::MoveRightCommand(GameObject* pGameObject)
	: MoveCommand(pGameObject)
{
}

void MoveRightCommand::Execute()
{
	if (m_pGameObject->GetScene() == SceneManager::GetInstance().GetActiveScene())
	{
		if (m_pMovementComp)
		{
			m_pMovementComp->SetMoveDirection(MovementComponent::MoveDirection::Right);
		}
	}
}