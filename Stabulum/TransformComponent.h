#pragma once
#include "BaseComponent.h"

class Transform;

class TransformComponent final : public BaseComponent
{
public:
	TransformComponent(float x = 0.f, float y = 0.f);

	virtual ~TransformComponent();
	TransformComponent(const TransformComponent& other) = delete;
	TransformComponent(TransformComponent&& other) = delete;
	TransformComponent& operator=(const TransformComponent& other) = delete;
	TransformComponent& operator=(TransformComponent&& other) = delete;

	virtual void Update() override;

	TransformComponent* SetPosition(float x, float y);
	Transform* GetTransform() { return m_pTransform; }

private:
	Transform* m_pTransform;
};