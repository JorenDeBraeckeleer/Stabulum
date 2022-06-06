#include "BurgerTimePCH.h"
#include "HealthComponent.h"

#include "PeterPepperComponent.h"
#include "TextComponent.h"

HealthComponent::HealthComponent()
	: m_pTextComp{ nullptr }
{
}

void HealthComponent::Update()
{
	if (!m_HasComponentsCached)
	{
		m_pTextComp = m_pGameObject->GetComponent<TextComponent>();

		if (m_pTextComp)
		{
			m_HasComponentsCached = true;
		}
	}
}

void HealthComponent::OnNotify(GameObject* pGameObject, const GameEvent& event)
{
	if (!m_HasComponentsCached)
	{
		return;
	}

	switch (event)	
	{
	case GameEvent::LostLife:
		m_pTextComp->SetText(std::to_string(pGameObject->GetComponent<PeterPepperComponent>()->GetNrLives()));
		break;
	case GameEvent::Died:
		m_pTextComp->SetText(std::to_string(pGameObject->GetComponent<PeterPepperComponent>()->GetNrLives()));
		break;
	case GameEvent::UpdateLives:
		m_pTextComp->SetText(std::to_string(pGameObject->GetComponent<PeterPepperComponent>()->GetNrLives()));
	default:
		break;
	}
}