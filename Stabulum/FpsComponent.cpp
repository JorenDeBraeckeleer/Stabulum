#include "StabulumPCH.h"
#include "FpsComponent.h"

#include "TextComponent.h"
#include "TimeManager.h"

FpsComponent::FpsComponent(TextComponent* pTextComponent)
	: m_pTextComponent{ pTextComponent }
	, m_Timer{ 0.f }
	, m_NrFps{ 0 }
{
}

void FpsComponent::Update()
{
	m_Timer += TimeManager::DeltaTime;
	++m_NrFps;

	if (m_Timer >= 0.25f)
	{
		int fps{ int(m_NrFps / m_Timer) };

		m_pTextComponent->SetText(std::to_string(fps));

		m_Timer = 0.f;
		m_NrFps = 0;
	}
}