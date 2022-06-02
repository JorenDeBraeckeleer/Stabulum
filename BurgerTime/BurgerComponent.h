#pragma once
#include "BaseComponent.h"

class BurgerComponent final : public BaseComponent, public Subject
{
public:
	BurgerComponent() = default;

	virtual ~BurgerComponent() = default;
	BurgerComponent(const BurgerComponent& other) = delete;
	BurgerComponent(BurgerComponent&& other) = delete;
	BurgerComponent& operator=(const BurgerComponent& other) = delete;
	BurgerComponent& operator=(BurgerComponent&& other) = delete;

	virtual void Update() override;

	void Dropped();
};