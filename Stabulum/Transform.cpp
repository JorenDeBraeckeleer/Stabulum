#include "StabulumPCH.h"
#include "Transform.h"

void Transform::SetPosition(const float x, const float y)
{
	m_Position.x = x;
	m_Position.y = y;
}

void Transform::SetPosition(const FVec2& pos)
{
	m_Position = pos;
}