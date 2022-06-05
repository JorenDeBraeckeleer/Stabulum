#pragma once
#include "BaseComponent.h"
#include "Transform.h"

class TransformComponent final : public BaseComponent
{
public:
	TransformComponent(float x = 0.f, float y = 0.f, bool inPixels = true);
	TransformComponent(const FVec2& pos, bool inPixels = true);

	virtual ~TransformComponent() = default;
	TransformComponent(const TransformComponent& other) = delete;
	TransformComponent(TransformComponent&& other) = delete;
	TransformComponent& operator=(const TransformComponent& other) = delete;
	TransformComponent& operator=(TransformComponent&& other) = delete;

	virtual void Update() override;

	const FVec2 GetWorldPosition(bool inPixels = true) const;
	const FVec2 GetLocalPosition(bool inPixels = true) const;
	void SetWorldPosition(float x, float y, bool inPixels = true);
	void SetWorldPosition(const FVec2& pos, bool inPixels = true);
	void SetLocalPosition(float x, float y, bool inPixels = true);
	void SetLocalPosition(const FVec2& pos, bool inPixels = true);

private:
	Transform m_Transform;
};