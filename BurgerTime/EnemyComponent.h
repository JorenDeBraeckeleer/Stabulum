#pragma once
#include "BaseComponent.h"

class EnemyComponent final : public BaseComponent, public Subject
{
public:
	EnemyComponent() = default;

	virtual ~EnemyComponent() = default;
	EnemyComponent(const EnemyComponent& other) = delete;
	EnemyComponent(EnemyComponent&& other) = delete;
	EnemyComponent& operator=(const EnemyComponent& other) = delete;
	EnemyComponent& operator=(EnemyComponent&& other) = delete;

	virtual void Update() override;

	void Died();
};