#pragma once
#include "ColliderComponent.h"

class RigidBodyComponent;

class BoxColliderComponent final : public ColliderComponent
{
public:
	BoxColliderComponent(RigidBodyComponent* pRigidBodyComponent, float width, float height, float centerX = 0.f, float centerY = 0.f, float angle = 0.f, int groupIndex = 0);
	virtual ~BoxColliderComponent() = default;

	BoxColliderComponent(const BoxColliderComponent& other) = delete;
	BoxColliderComponent(BoxColliderComponent&& other) = delete;
	BoxColliderComponent& operator=(const BoxColliderComponent& other) = delete;
	BoxColliderComponent& operator=(BoxColliderComponent&& other) = delete;

	virtual void Update() override;

	float GetWidth() { return m_Width; }
	float GetHeight() { return m_Height; }

	FVec2 GetCenter() { return FVec2{ m_CenterX, m_CenterY }; }

	float GetAngle() { return m_Angle; }

private:
	RigidBodyComponent* m_pRigidBodyComponent;

	float m_Width, m_Height, m_CenterX, m_CenterY, m_Angle;
	int m_GroupIndex;
};