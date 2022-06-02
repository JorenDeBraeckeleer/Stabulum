#include "StabulumPCH.h"
#include "TransformComponent.h"

TransformComponent::TransformComponent(float x, float y)
	: m_pTransform{ new Transform{} }
{
	m_pTransform->SetPosition(x, y, 0.f);
}

TransformComponent::~TransformComponent()
{
	delete m_pTransform;
	m_pTransform = nullptr;
}

void TransformComponent::Update()
{
}

TransformComponent* TransformComponent::SetPosition(float x, float y)
{
	m_pTransform->SetPosition(x, y, 0.0f);

	return this;
}