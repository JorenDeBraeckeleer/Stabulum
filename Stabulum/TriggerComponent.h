#pragma once
#include "BaseComponent.h"

class ColliderComponent;

class TriggerComponent final : public BaseComponent
{
public:
	TriggerComponent() = default;

	virtual ~TriggerComponent() = default;
	TriggerComponent(const TriggerComponent& other) = delete;
	TriggerComponent(TriggerComponent&& other) = delete;
	TriggerComponent& operator=(const TriggerComponent& other) = delete;
	TriggerComponent& operator=(TriggerComponent&& other) = delete;

	virtual void Update() override;

	void OnTriggerEnter(ColliderComponent* pCollider);

private:
};