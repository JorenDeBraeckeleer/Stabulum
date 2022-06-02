#include "StabulumPCH.h"
#include "Transform.h"

void Transform::SetPosition(const float x, const float y, const float z)
{
	m_Position.x = x;
	m_Position.y = y;
	m_Position.z = z;
}

//void Transform::SetPosition(const FVec3& pos)
//{
//	m_Position = pos;
//}

void Transform::SetPosition(const glm::vec3& pos)
{
	m_Position = pos;
}