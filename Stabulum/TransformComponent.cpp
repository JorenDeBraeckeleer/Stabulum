#include "StabulumPCH.h"
#include "TransformComponent.h"

TransformComponent::TransformComponent(float x, float y)
	: m_FVec2Pos{ FVec2{ x, y } }
	, m_PixelsPerUnit{ 16 }
{
	m_FVec2Pos = m_FVec2Pos / m_PixelsPerUnit;
}

TransformComponent::TransformComponent(const FVec2& pos)
	: TransformComponent{ pos.x, pos.y }
{
}

void TransformComponent::Update()
{
}

void TransformComponent::SetPixelPosition(float x, float y)
{
	m_FVec2Pos.x = x / m_PixelsPerUnit;
	m_FVec2Pos.y = y / m_PixelsPerUnit;
}

void TransformComponent::SetPixelPosition(const FVec2& pos)
{
	m_FVec2Pos = pos / m_PixelsPerUnit;
}

FVec2 TransformComponent::GetPixelPosition()
{
	return m_FVec2Pos * m_PixelsPerUnit;
}

void TransformComponent::SetUnitPosition(float x, float y)
{
	m_FVec2Pos.x = x;
	m_FVec2Pos.y = y;
}

void TransformComponent::SetUnitPosition(const FVec2& pos)
{
	m_FVec2Pos = pos;
}

FVec2 TransformComponent::GetUnitPosition()
{
	return m_FVec2Pos;
}