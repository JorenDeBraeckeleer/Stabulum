#pragma once
#include "BaseComponent.h"

class Transform;

class TransformComponent final : public BaseComponent
{
public:
	TransformComponent(float x = 0.f, float y = 0.f);
	TransformComponent(const FVec2& pos);

	virtual ~TransformComponent() = default;
	TransformComponent(const TransformComponent& other) = delete;
	TransformComponent(TransformComponent&& other) = delete;
	TransformComponent& operator=(const TransformComponent& other) = delete;
	TransformComponent& operator=(TransformComponent&& other) = delete;

	virtual void Update() override;

	void SetPixelPosition(float x, float y);
	void SetPixelPosition(const FVec2& pos);
	FVec2 GetPixelPosition();

	void SetUnitPosition(float x, float y);
	void SetUnitPosition(const FVec2& pos);
	FVec2 GetUnitPosition();

	void SetUnit(int pixelsPerUnit) { m_PixelsPerUnit = pixelsPerUnit; }

private:
	FVec2 m_FVec2Pos;
	int m_PixelsPerUnit;
};