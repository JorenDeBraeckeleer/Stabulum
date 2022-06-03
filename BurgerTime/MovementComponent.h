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

	void CheckBlockDirection(const FVec2& characterPosition, const FVec2& otherPosition);
	void CheckUnBlockDirection(const FVec2& characterPosition, const FVec2& otherPosition);
	void BlockDirection(const MoveDirection& moveDirection, bool block = true);

private:
	MoveDirection m_MoveDirection;
	SpriteComponent* m_pSpriteComponent;
	RigidBodyComponent* m_pRigidBodyComponent;

	bool m_CanWalkUp, m_CanWalkDown, m_CanWalkLeft, m_CanWalkRight;
	bool m_IsOnLadder, m_IsMoving, m_HasUpdatedMovement;
	MoveDirection m_LastInput;
};