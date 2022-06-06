#pragma once

#include "Structs.h"

class Transform final
{
public:
	Transform(float x, float y, bool inPixels = true);
	~Transform() = default;

	Transform(const Transform&) = delete;
	Transform(Transform&&) = delete;
	Transform& operator= (const Transform&) = delete;
	Transform& operator= (const Transform&&) = delete;

	const FVec2 GetWorldPosition(bool inPixels = true) const;
	const FVec2 GetLocalPosition(bool inPixels = true) const;
	void SetWorldPosition(float x, float y, bool inPixels = true);
	void SetWorldPosition(const FVec2& pos, bool inPixels = true);
	void SetLocalPosition(float x, float y, bool inPixels = true);
	void SetLocalPosition(const FVec2& pos, bool inPixels = true);

private:
	FVec2 m_WorldPosition;
	FVec2 m_LocalPosition;

	int m_PixelsPerUnit;
};