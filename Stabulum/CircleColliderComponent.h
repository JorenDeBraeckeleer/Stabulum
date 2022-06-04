#pragma once
#include "ColliderComponent.h"

class RigidBodyComponent;
class b2Fixture;

class CircleColliderComponent final : public ColliderComponent
{
public:
	CircleColliderComponent(RigidBodyComponent* pRigidBodyComponent, float radius, FVec2 point = FVec2{ 0.f, 0.f });

	virtual ~CircleColliderComponent() = default;
	CircleColliderComponent(const CircleColliderComponent& other) = delete;
	CircleColliderComponent(CircleColliderComponent&& other) = delete;
	CircleColliderComponent& operator=(const CircleColliderComponent& other) = delete;
	CircleColliderComponent& operator=(CircleColliderComponent&& other) = delete;

	virtual void Update() override;

	float GetRadius() { return m_Radius; }

	FVec2 GetPoint() { return m_Point; }

private:
	RigidBodyComponent* m_pRigidBodyComponent;

	float m_Radius;
	FVec2 m_Point;
};