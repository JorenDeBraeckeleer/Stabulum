#pragma once
#include "BaseComponent.h"

#include "b2_math.h"
class b2World;

class ContactListener;
class TransformComponent;
class RigidBodyComponent;
class BoxColliderComponent;

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

	void AddToBodyColliderBox(RigidBodyComponent* pRigidBodyComponent, BoxColliderComponent* pBoxColliderComponent);

private:
	b2World* m_pWorld;
	ContactListener* m_pContactListener;
	std::vector<RigidBodyComponent*> m_pRigidBodyComponents;

	b2Vec2 GetVecb2(FVec2 vec) { return b2Vec2{ vec.x, vec.y }; }
	FVec2 GetFVec(b2Vec2 vec) { return FVec2{ vec.x, vec.y }; }
};