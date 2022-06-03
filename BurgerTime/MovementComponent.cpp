#include "BurgerTimePCH.h"
#include "MovementComponent.h"

#include "SpriteComponent.h"
#include "RigidBodyComponent.h"

MovementComponent::MovementComponent(SpriteComponent* pSpriteComponent, RigidBodyComponent* pRigidBodyComponent)
	: m_MoveDirection{ MoveDirection::Idle }
	, m_pSpriteComponent{ pSpriteComponent }
	, m_pRigidBodyComponent{ pRigidBodyComponent }
	, m_CanWalkUp{ true }
	, m_CanWalkDown{ true }
	, m_CanWalkLeft{ true }
	, m_CanWalkRight{ true }
	, m_IsOnLadder{}
	, m_IsMoving{}
	, m_HasUpdatedMovement{}
	, m_LastInput{ m_MoveDirection }
{
}

void MovementComponent::Update()
{
	if (m_LastInput == m_MoveDirection && !m_HasUpdatedMovement)
	{
		m_MoveDirection = MoveDirection::Idle;
	}

	switch (m_MoveDirection)
	{
	case MovementComponent::MoveDirection::Idle:

		m_IsMoving = false;

		m_pSpriteComponent->SetCurrentCollumn(1);
		m_pSpriteComponent->SetCurrentRow(1);

		if (m_IsOnLadder && m_LastInput == MoveDirection::Up)
		{
			m_pSpriteComponent->SetCurrentRow(static_cast<int>(m_LastInput));
		}

		break;
	case MovementComponent::MoveDirection::Up:

		if (!m_CanWalkUp)
		{
			m_IsMoving = false;
			break;
		}

		m_IsMoving = true;

		m_pSpriteComponent->SetCurrentRow(static_cast<int>(m_MoveDirection));

		m_LastInput = m_MoveDirection;

		break;
	case MovementComponent::MoveDirection::Down:

		if (!m_CanWalkDown)
		{
			m_IsMoving = false;
			break;
		}

		m_IsMoving = true;

		m_pSpriteComponent->SetCurrentRow(static_cast<int>(m_MoveDirection));

		m_LastInput = m_MoveDirection;

		break;
	case MovementComponent::MoveDirection::Left:

		if (!m_CanWalkLeft)
		{
			m_IsMoving = false;
			break;
		}

		if (m_IsOnLadder)
		{
			m_IsMoving = false;

			m_pSpriteComponent->SetCurrentCollumn(1);
			m_pSpriteComponent->SetCurrentRow(1);
		}
		else
		{
			m_IsMoving = true;

			m_pSpriteComponent->SetCurrentRow(static_cast<int>(m_MoveDirection));
		}

		m_LastInput = m_MoveDirection;

		break;
	case MovementComponent::MoveDirection::Right:

		if (!m_CanWalkRight)
		{
			m_IsMoving = false;
			break;
		}

		if (m_IsOnLadder)
		{
			m_IsMoving = false;

			m_pSpriteComponent->SetCurrentCollumn(1);
			m_pSpriteComponent->SetCurrentRow(1);
		}
		else
		{
			m_IsMoving = true;

			m_pSpriteComponent->SetCurrentRow(static_cast<int>(m_MoveDirection));
		}

		m_LastInput = m_MoveDirection;

		break;
	default:
		break;
	}

	if (m_IsMoving)
	{
		FVec2 direction{};

		switch (m_MoveDirection)
		{
		case MovementComponent::MoveDirection::Up:
			direction = { 0.f, -1.f };
			break;
		case MovementComponent::MoveDirection::Down:
			direction = { 0.f, 1.f };
			break;
		case MovementComponent::MoveDirection::Left:
			direction = { -1.f, 0.f };
			break;
		case MovementComponent::MoveDirection::Right:
			direction = { 1.f, 0.f };
			break;
		default:
			break;
		}

		FVec2 speed{ 4.f, 3.f };
		m_pRigidBodyComponent->UpdateLinearVelocity(direction * speed);
	}
	else
	{
		m_pRigidBodyComponent->UpdateLinearVelocity(0.f, 0.f);
	}

	m_pSpriteComponent->SetIsMoving(m_IsMoving);
	m_HasUpdatedMovement = false;
}

void MovementComponent::CheckBlockDirection(const FVec2& characterPosition, const FVec2& otherPosition)
{
	switch (m_MoveDirection)
	{
	case MovementComponent::MoveDirection::Up:
		if (characterPosition.y > otherPosition.y)
		{
			BlockDirection(MoveDirection::Up);
		}
		break;
	case MovementComponent::MoveDirection::Down:
		if (characterPosition.y < otherPosition.y)
		{
			BlockDirection(MoveDirection::Down);
		}
		break;
	case MovementComponent::MoveDirection::Left:
		if (characterPosition.x > otherPosition.x)
		{
			BlockDirection(MoveDirection::Left);
		}
		break;
	case MovementComponent::MoveDirection::Right:
		if (characterPosition.x < otherPosition.x)
		{
			BlockDirection(MoveDirection::Right);
		}
		break;
	default:
		break;
	}
}

void MovementComponent::CheckUnBlockDirection(const FVec2& characterPosition, const FVec2& otherPosition)
{
	switch (m_MoveDirection)
	{
	case MovementComponent::MoveDirection::Up:
		if (characterPosition.y < otherPosition.y)
		{
			BlockDirection(MoveDirection::Down, false);
		}
		break;
	case MovementComponent::MoveDirection::Down:
		if (characterPosition.y > otherPosition.y)
		{
			BlockDirection(MoveDirection::Up, false);
		}
		break;
	case MovementComponent::MoveDirection::Left:
		if (characterPosition.x < otherPosition.x)
		{
			BlockDirection(MoveDirection::Right, false);
		}
		break;
	case MovementComponent::MoveDirection::Right:
		if (characterPosition.x > otherPosition.x)
		{
			BlockDirection(MoveDirection::Left, false);
		}
		break;
	default:
		break;
	}
}

void MovementComponent::BlockDirection(const MoveDirection& moveDirection, bool block)
{
	switch (moveDirection)
	{
	case MovementComponent::MoveDirection::Up:
		m_CanWalkUp = !block;
		break;
	case MovementComponent::MoveDirection::Down:
		m_CanWalkDown = !block;
		break;
	case MovementComponent::MoveDirection::Left:
		m_CanWalkLeft = !block;
		break;
	case MovementComponent::MoveDirection::Right:
		m_CanWalkRight = !block;
		break;
	default:
		break;
	}
}