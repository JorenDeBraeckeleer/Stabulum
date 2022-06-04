#include "StabulumPCH.h"
#include "ColliderComponent.h"

ColliderComponent::ColliderComponent()
	: m_IsSensor{ false }
	, m_Friction{ 0.2f }
	, m_Restitution{ 0.f }
	, m_RestitutionTreshold{ 1.f }
	, m_Density{ 1.f }
	, m_pPhysicsFixture{}
	, m_IsUpdateNeeded{ true }
{
}