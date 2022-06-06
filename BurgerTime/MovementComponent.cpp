#include "BurgerTimePCH.h"
#include "MovementComponent.h"

#include "RigidBodyComponent.h"
#include "SpriteComponent.h"

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
		FVec2 desiredVelocity{};

		switch (m_MoveDirection)
		{
		case MovementComponent::MoveDirection::Up:
			desiredVelocity = { 0.f, -3.f };
			break;
		case MovementComponent::MoveDirection::Down:
			desiredVelocity = { 0.f, 3.f };
			break;
		case MovementComponent::MoveDirection::Left:
			desiredVelocity = { -4.f, 0.f };
			break;
		case MovementComponent::MoveDirection::Right:
			desiredVelocity = { 4.f, 0.f };
			break;
		default:
			break;
		}

		m_pRigidBodyComponent->SetBodyLinearVelocity(desiredVelocity.x, desiredVelocity.y);
	}
	else
	{
		m_pRigidBodyComponent->SetBodyLinearVelocity(0.f, 0.f);
	}

	m_pSpriteComponent->SetIsMoving(m_IsMoving);
	m_HasUpdatedMovement = false;
}