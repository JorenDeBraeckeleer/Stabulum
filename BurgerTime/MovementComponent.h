#pragma once
#include "BaseComponent.h"

class SpriteComponent;
class RigidBodyComponent;

class MovementComponent final : public BaseComponent
{
public:
	MovementComponent(SpriteComponent* pSpriteComponent, RigidBodyComponent* pRigidBodyComponent);

	virtual ~MovementComponent() = default;
	MovementComponent(const MovementComponent& other) = delete;
	MovementComponent(MovementComponent&& other) = delete;
	MovementComponent& operator=(const MovementComponent& other) = delete;
	MovementComponent& operator=(MovementComponent&& other) = delete;

	enum class MoveDirection
	{
		Idle = 4,
		Up = 0,
		Down = 1,
		Left = 2,
		Right = 3,
	};

	virtual void Update() override;

	void SetMoveDirection(const MoveDirection& moveDirection) { m_MoveDirection = moveDirection; m_HasUpdatedMovement = true; }

private:
	MoveDirection m_MoveDirection;
	SpriteComponent* m_pSpriteComponent;
	RigidBodyComponent* m_pRigidBodyComponent;

	bool m_IsOnLadder, m_IsMoving, m_HasUpdatedMovement;
	MoveDirection m_LastInput;
};