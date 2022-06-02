#include "BurgerTimePCH.h"
#include "MovementComponent.h"

#include "SpriteComponent.h"
#include "RigidBodyComponent.h"

MovementComponent::MovementComponent(SpriteComponent* pSpriteComponent, RigidBodyComponent* pRigidBodyComponent)
	: m_MoveDirection{ MoveDirection::Idle }
	, m_pSpriteComponent{ pSpriteComponent }
	, m_pRigidBodyComponent{ pRigidBodyComponent }
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

		m_IsMoving = true;

		m_pSpriteComponent->SetCurrentRow(static_cast<int>(m_MoveDirection));

		m_LastInput = m_MoveDirection;

		break;
	case MovementComponent::MoveDirection::Down:

		m_IsMoving = true;

		m_pSpriteComponent->SetCurrentRow(static_cast<int>(m_MoveDirection));

		m_LastInput = m_MoveDirection;

		break;
	case MovementComponent::MoveDirection::Left:

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
		glm::vec2 direction{};

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

		float speed{ 10.f };
		m_pRigidBodyComponent->UpdateLinearVelocity(direction.x * speed, direction.y * speed);
	}
	else
	{
		m_pRigidBodyComponent->UpdateLinearVelocity(0.f, 0.f);
	}

	m_pSpriteComponent->SetIsMoving(m_IsMoving);
	m_HasUpdatedMovement = false;
}