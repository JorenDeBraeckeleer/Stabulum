#pragma once
#include "BaseComponent.h"
#include <functional>
class b2Fixture;

class ColliderComponent : public BaseComponent
{
public:
	ColliderComponent();

	virtual ~ColliderComponent() = default;
	ColliderComponent(const ColliderComponent& other) = delete;
	ColliderComponent(ColliderComponent&& other) = delete;
	ColliderComponent& operator=(const ColliderComponent& other) = delete;
	ColliderComponent& operator=(ColliderComponent&& other) = delete;

	virtual void Update() override = 0;

	std::function<void(ColliderComponent*)> OnTriggerEnter;
	std::function<void(ColliderComponent*)> OnTriggerExit;

	void SetSensor(bool isSensor = true) { m_IsSensor = isSensor; }
	bool GetIsSensor() { return m_IsSensor; }

	void SetPhysicsMaterial(float friction = 0.2f, float restitution = 0.f, float restitutionTreshold = 1.f, float density = 1.f)
	{
		m_Friction = friction; m_Restitution = restitution; m_RestitutionTreshold = restitutionTreshold; m_Density = density;
	}

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

protected:
	bool m_IsSensor;

	float m_Friction, m_Restitution, m_RestitutionTreshold, m_Density;

	b2Fixture* m_pPhysicsFixture;

	bool m_IsUpdateNeeded;
};