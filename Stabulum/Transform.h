#pragma once
#include "Structs.h"

class Transform final
{
public:
	const FVec2 GetPosition() const { return m_Position; }
	void SetPosition(float x, float y);
	void SetPosition(const FVec2& pos);

private:
	FVec2 m_Position;
};