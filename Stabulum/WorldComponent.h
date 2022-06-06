#pragma once
#include "BaseComponent.h"

#include "b2_math.h"

class b2World;
class b2Shape;

class BoxColliderComponent;
class CircleColliderComponent;
class ContactListener;
class RigidBodyComponent;
class TransformComponent;

class WorldComponent final : public BaseComponent
{
public:
	WorldComponent();
	virtual ~WorldComponent();

	WorldComponent(const WorldComponent& other) = delete;
	WorldComponent(WorldComponent&& other) = delete;
	WorldComponent& operator=(const WorldComponent& other) = delete;
	WorldComponent& operator=(WorldComponent&& other) = delete;

	virtual void Update() override;
	virtual void FixedUpdate() override;

	void AddBody(TransformComponent* pTransformComponent, RigidBodyComponent* pRigidBodyComponent);
	void RemoveBody(RigidBodyComponent* pRigidBodyComponent);

	void AddToBodyCollider(const b2Shape& shape, RigidBodyComponent* pRigidBodyComponent, ColliderComponent* pColliderComponent, int16 groupIndex = 0);
	void AddToBodyColliderBox(RigidBodyComponent* pRigidBodyComponent, BoxColliderComponent* pBoxColliderComponent, int16 groupIndex = 0);
	void AddToBodyColliderCircle(RigidBodyComponent* pRigidBodyComponent, CircleColliderComponent* pCircleColliderComponent, int16 groupIndex = 0);

private:
	b2Vec2 GetVecb2(FVec2 vec) { return b2Vec2{ vec.x, vec.y }; }
	FVec2 GetFVec(b2Vec2 vec) { return FVec2{ vec.x, vec.y }; }

	b2World* m_pWorld;
	ContactListener* m_pContactListener;
	std::vector<RigidBodyComponent*> m_pRigidBodyComponents;
};