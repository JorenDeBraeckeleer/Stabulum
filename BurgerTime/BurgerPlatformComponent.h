#pragma once

#include "BaseComponent.h"

class ColliderComponent;

class BurgerPlatformComponent final : public BaseComponent
{
public:
	BurgerPlatformComponent() = default;
	virtual ~BurgerPlatformComponent() = default;

	BurgerPlatformComponent(const BurgerPlatformComponent& other) = delete;
	BurgerPlatformComponent(BurgerPlatformComponent&& other) = delete;
	BurgerPlatformComponent& operator=(const BurgerPlatformComponent& other) = delete;
	BurgerPlatformComponent& operator=(BurgerPlatformComponent&& other) = delete;

	virtual void Update() override;

	void OnTriggerEnter(ColliderComponent* pCollider);
	void OnTriggerExit(ColliderComponent* pCollider);

private:

};