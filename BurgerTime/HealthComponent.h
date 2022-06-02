#pragma once
#include "BaseComponent.h"

class TextComponent;

class HealthComponent final : public BaseComponent, public Observer
{
public:
	HealthComponent();

	virtual ~HealthComponent() = default;
	HealthComponent(const HealthComponent& other) = delete;
	HealthComponent(HealthComponent&& other) = delete;
	HealthComponent& operator=(const HealthComponent& other) = delete;
	HealthComponent& operator=(HealthComponent&& other) = delete;

	virtual void Update() override;

	virtual void OnNotify(GameObject* pGameObject, const GameEvent& event) override;

private:
	TextComponent* m_pTextComp;
};