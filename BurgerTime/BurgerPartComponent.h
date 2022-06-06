#pragma once

#include "BaseComponent.h"

class ColliderComponent;

class BurgerPartComponent final : public BaseComponent
{
public:
	BurgerPartComponent();
	virtual ~BurgerPartComponent() = default;

	BurgerPartComponent(const BurgerPartComponent& other) = delete;
	BurgerPartComponent(BurgerPartComponent&& other) = delete;
	BurgerPartComponent& operator=(const BurgerPartComponent& other) = delete;
	BurgerPartComponent& operator=(BurgerPartComponent&& other) = delete;

	virtual void Update() override;

	void OnTriggerEnter(ColliderComponent* pCollider);

	bool IsHit() { return m_IsHit; }
	void ResetHit();

private:
	bool m_IsHit;
};