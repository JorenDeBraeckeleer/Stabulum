#pragma once
#include "Structs.h"

class Transform final
{
public:
	//const FVec3 GetPosition() const { return m_Position; }
	const glm::vec3 GetPosition() const { return m_Position; }
	void SetPosition(float x, float y, float z);
	//void SetPosition(const FVec3& pos);
	void SetPosition(const glm::vec3& pos);

private:
	//FVec3 m_Position;
	glm::vec3 m_Position;
};