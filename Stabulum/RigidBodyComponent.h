#pragma once
#include "BaseComponent.h"

class b2Body;

class TransformComponent;

class RigidBodyComponent final : public BaseComponent
{
public:
	enum class BodyType
	{
		Static = 0,
		Kinematic = 1,
		Dynamic = 2,
	};

	RigidBodyComponent(TransformComponent* pTransformComponent, BodyType bodyType = BodyType::Static, float angle = 0.f, float gravityScale = 1.f, bool hasFixedRotation = false);

	virtual ~RigidBodyComponent() = default;
	RigidBodyComponent(const RigidBodyComponent& other) = delete;
	RigidBodyComponent(RigidBodyComponent&& other) = delete;
	RigidBodyComponent& operator=(const RigidBodyComponent& other) = delete;
	RigidBodyComponent& operator=(RigidBodyComponent&& other) = delete;

	virtual void Update() override;

	void UpdatePosition();
	void UpdateLinearVelocity(float velocityX, float velocityY);

	float GetAngle() { return m_Angle; }

	float GetGravityScale() { return m_GravityScale; }

	bool GetHasFixedRotation() { return m_HasFixedRotation; }

	void SetLinearVelocity(float velocityX, float velocityY) { m_LinearVelocity.x = velocityX; m_LinearVelocity.y = velocityY; }
	glm::vec2 GetLinearVelocity() { return m_LinearVelocity; }

	void SetAngularVelocity(float velocity) { m_AngularVelocity = velocity; }
	float GetAngularVelocity() { return m_AngularVelocity; }

	void SetLinearDamping(float damping) { m_LinearDamping = damping; }
	float GetLinearDamping() { return m_LinearDamping; }

	void SetAngularDamping(float damping) { m_AngularDamping = damping; }
	float GetAngularDamping() { return m_AngularDamping; }

	void SetAllowSleep(bool allowSleep = true) { m_AllowSleep = allowSleep; }
	bool GetAllowSleep() { return m_AllowSleep; }

	void SetAwake(bool isAwake = true) { m_IsAwake = isAwake; }
	bool GetIsAwake() { return m_IsAwake; }

	void SetBullet(bool isBullet = true) { m_IsBullet = isBullet; }
	bool GetIsBullet() { return m_IsBullet; }

	void SetEnabled(bool isEnabled = true) { m_IsEnabled = isEnabled; }
	bool GetIsEnabled() { return m_IsEnabled; }

	BodyType GetBodyType() { return m_BodyType; }

	b2Body* GetPhysicsBody() { return m_pPhysicsBody; }
	void SetPhysicsBody(b2Body* pBody) { m_pPhysicsBody = pBody; }

private:
	glm::vec2 m_LinearVelocity;
	float m_Angle, m_AngularVelocity, m_LinearDamping, m_AngularDamping, m_GravityScale;
	bool m_AllowSleep, m_IsAwake, m_HasFixedRotation, m_IsBullet, m_IsEnabled;

	TransformComponent* m_pTransformComponent;

	BodyType m_BodyType;

	b2Body* m_pPhysicsBody;

	bool m_IsUpdateNeeded;
};