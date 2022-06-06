#include "BurgerTimePCH.h"
#include "ScoreComponent.h"

#include "TextComponent.h"

ScoreComponent::ScoreComponent(int score)
	: m_Score{ score }
	, m_IsUpdateNeeded{ true }
{
}

void ScoreComponent::Update()
{
	if (m_IsUpdateNeeded)
	{
		m_pGameObject->GetComponent<TextComponent>()->SetText(std::to_string(m_Score));

		m_IsUpdateNeeded = false;
	}
}

void ScoreComponent::OnNotify(GameObject*, const GameEvent& event)
{
	switch (event)
	{
	case GameEvent::BurgerDropped:
		m_Score += 50;
		m_pGameObject->GetComponent<TextComponent>()->SetText(std::to_string(m_Score));
		break;
	case GameEvent::EnemyDied:
		m_Score += 100;
		m_pGameObject->GetComponent<TextComponent>()->SetText(std::to_string(m_Score));
		break;
	default:
		break;
	}
}