#include "StabulumPCH.h"
#include "Transform.h"

Transform::Transform(float x, float y, bool inPixels)
	: m_WorldPosition{ FVec2{} }
	, m_LocalPosition{ FVec2{} }
	, m_PixelsPerUnit{ 16 }
{
	SetLocalPosition(x, y, inPixels);
	SetWorldPosition(x, y, inPixels);
}

const FVec2 Transform::GetWorldPosition(bool inPixels) const
{
	if (inPixels)
	{
		return m_WorldPosition;
	}
	else
	{
		return m_WorldPosition / m_PixelsPerUnit;
	}
}

const FVec2 Transform::GetLocalPosition(bool inPixels) const
{
	if (inPixels)
	{
		return m_LocalPosition;
	}
	else
	{
		return m_LocalPosition / m_PixelsPerUnit;
	}
}

void Transform::SetWorldPosition(const float x, const float y, bool inPixels)
{
	if (inPixels)
	{
		m_WorldPosition.x = x;
		m_WorldPosition.y = y;
	}
	else
	{
		m_WorldPosition.x = x * m_PixelsPerUnit;
		m_WorldPosition.y = y * m_PixelsPerUnit;
	}
}

void Transform::SetWorldPosition(const FVec2& pos, bool inPixels)
{
	SetWorldPosition(pos.x, pos.y, inPixels);
}

//void Transform::AddWorldPosition(float x, float y, bool inPixels = true)
//{
//	if (inPixels)
//	{
//		m_WorldPosition.x = m_WorldPosition.x + x;
//		m_WorldPosition.y = m_WorldPosition.y + y;
//	}
//	else
//	{
//		m_WorldPosition.x = m_WorldPosition.x + x * m_PixelsPerUnit;
//		m_WorldPosition.y = m_WorldPosition.y + y * m_PixelsPerUnit;
//	}
//}
//
//void Transform::AddWorldPosition(const FVec2& pos, bool inPixels = true)
//{
//	AddWorldPosition(pos.x, pos.y, inPixels);
//}

void Transform::SetLocalPosition(const float x, const float y, bool inPixels)
{
	if (inPixels)
	{
		m_LocalPosition.x = x;
		m_LocalPosition.y = y;
	}
	else
	{
		m_LocalPosition.x = x * m_PixelsPerUnit;
		m_LocalPosition.y = y * m_PixelsPerUnit;
	}
}

void Transform::SetLocalPosition(const FVec2& pos, bool inPixels)
{
	SetLocalPosition(pos.x, pos.y, inPixels);
}