#include "StabulumPCH.h"
#include "TransformComponent.h"

TransformComponent::TransformComponent(float x, float y, bool inPixels)
	: m_Transform{ Transform{ x, y, inPixels } }
{
}

TransformComponent::TransformComponent(const FVec2& pos, bool inPixels)
	: TransformComponent{ pos.x, pos.y, inPixels }
{
}

void TransformComponent::Update()
{
}

const FVec2 TransformComponent::GetWorldPosition(bool inPixels) const
{
	return m_Transform.GetWorldPosition(inPixels);
}

const FVec2 TransformComponent::GetLocalPosition(bool inPixels) const
{
	return m_Transform.GetLocalPosition(inPixels);
}

void TransformComponent::SetWorldPosition(const float x, const float y, bool inPixels)
{
	m_Transform.SetWorldPosition(x, y, inPixels);

	if (GameObject* pParent = GetGameObject()->GetParent())
	{
		if (TransformComponent* pParentComp = pParent->GetComponent<TransformComponent>())
		{
			FVec2 pos = m_Transform.GetWorldPosition(inPixels) - pParentComp->GetWorldPosition(inPixels);
			m_Transform.SetLocalPosition(pos, inPixels);
		}
	}

	for (GameObject* pChild : GetGameObject()->GetChildren())
	{
		if (TransformComponent* pChildComp = pChild->GetComponent<TransformComponent>())
		{
			FVec2 pos = m_Transform.GetWorldPosition(inPixels) + pChildComp->GetLocalPosition(inPixels);
			pChildComp->SetWorldPosition(pos, inPixels);
		}
	}
}

void TransformComponent::SetWorldPosition(const FVec2& pos, bool inPixels)
{
	SetWorldPosition(pos.x, pos.y, inPixels);
}

void TransformComponent::SetLocalPosition(const float x, const float y, bool inPixels)
{
	m_Transform.SetLocalPosition(x, y, inPixels);

	if (GameObject* pParent = GetGameObject()->GetParent())
	{
		if (TransformComponent* pParentComp = pParent->GetComponent<TransformComponent>())
		{
			FVec2 pos = pParentComp->GetWorldPosition(inPixels) + m_Transform.GetLocalPosition(inPixels);
			m_Transform.SetWorldPosition(pos, inPixels);
		}
	}

	for (GameObject* pChild : GetGameObject()->GetChildren())
	{
		if (TransformComponent* pChildComp = pChild->GetComponent<TransformComponent>())
		{
			FVec2 pos = m_Transform.GetWorldPosition(inPixels) + pChildComp->GetLocalPosition(inPixels);
			pChildComp->SetWorldPosition(pos, inPixels);
		}
	}
}

void TransformComponent::SetLocalPosition(const FVec2& pos, bool inPixels)
{
	SetLocalPosition(pos.x, pos.y, inPixels);
}