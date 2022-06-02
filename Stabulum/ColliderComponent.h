#pragma once
#include "BaseComponent.h"

class ColliderComponent : public BaseComponent
{
public:
	ColliderComponent() = default;

	virtual ~ColliderComponent() = default;
	ColliderComponent(const ColliderComponent& other) = delete;
	ColliderComponent(ColliderComponent&& other) = delete;
	ColliderComponent& operator=(const ColliderComponent& other) = delete;
	ColliderComponent& operator=(ColliderComponent&& other) = delete;

	virtual void Update() override = 0;

protected:
	
};