#pragma once
#include "ColliderComponent.h"

class RigidBodyComponent;
class b2Fixture;

class BoxColliderComponent final : public ColliderComponent
{
public:
	BoxColliderComponent(RigidBodyComponent* pRigidBodyComponent, float width, float height, float centerX = 0.f, float centerY = 0.f, float angle = 0.f);

	virtual ~BoxColliderComponent() = default;
	BoxColliderComponent(const BoxColliderComponent& other) = delete;
	BoxColliderComponent(BoxColliderComponent&& other) = delete;
	BoxColliderComponent& operator=(const BoxColliderComponent& other) = delete;
	BoxColliderComponent& operator=(BoxColliderComponent&& other) = delete;

	virtual void Update() override;

	float GetWidth() { return m_Width; }
	float GetHeight() { return m_Height; }

	glm::vec2 GetCenter() { return glm::vec2{ m_CenterX, m_CenterY }; }

	float GetAngle() { return m_Angle; }

	void SetSensor(bool isSensor = true) { m_IsSensor = isSensor; }
	bool GetIsSensor() { return m_IsSensor; }

	void SetPhysicsMaterial(float friction = 0.2f, float restitution = 0.f, float restitutionTreshold = 1.f, float density = 0.f)
									{ m_Friction = friction; m_Restitution = restitution; m_RestitutionTreshold = restitutionTreshold; m_Density = density; }

	void SetFriction(float friction) { m_Friction = friction; }
	float GetFriction() { return m_Friction; }

	void SetRestitution(float restitution) { m_Restitution = restitution; }
	float GetRestitution() { return m_Restitution; }

	void SetRestitutionTreshold(float restitutionTreshold) { m_RestitutionTreshold = restitutionTreshold; }
	float GetRestitutionTreshold() { return m_RestitutionTreshold; }

	void SetDensity(float density) { m_Density = density; }
	float GetDensity() { return m_Density; }

	b2Fixture* GetPhysicsFixture() { return m_pPhysicsFixture; }
	void SetPhysicsFixture(b2Fixture* pFixture) { m_pPhysicsFixture = pFixture; }

private:
	RigidBodyComponent* m_pRigidBodyComponent;

	float m_Width, m_Height, m_CenterX, m_CenterY, m_Angle;
	bool m_IsSensor;
	float m_Friction, m_Restitution, m_RestitutionTreshold, m_Density;

	b2Fixture* m_pPhysicsFixture;

	bool m_IsUpdateNeeded;
};