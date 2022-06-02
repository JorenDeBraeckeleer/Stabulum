#include "BurgerTimePCH.h"
#include "PeterPepperComponent.h"
#include "ServiceLocator.h"

PeterPepperComponent::PeterPepperComponent(int nrLives)
	: m_NrLives{ nrLives }
	, m_IsUpdateNeeded{ true }
{
	//Sound Test
	ServiceLocator::GetSoundManager()->Load("TestSound.mp3", 1);

	if (nrLives > 0)
	{
		m_IsDead = false;
	}
	else
	{
		m_IsDead = true;
	}
}

void PeterPepperComponent::Update()
{
	if (m_IsUpdateNeeded)
	{
		if (m_IsDead)
		{
			Notify(m_pGameObject, GameEvent::Died);
		}
		else
		{
			Notify(m_pGameObject, GameEvent::UpdateLives);
		}

		m_IsUpdateNeeded = false;
	}
}

void PeterPepperComponent::LostLife()
{
	//Sound Test
	ServiceLocator::GetSoundManager()->Play(1, 10);

	if (m_IsDead)
	{
		return;
	}

	--m_NrLives;

	if (m_NrLives > 0)
	{
		Notify(m_pGameObject, GameEvent::LostLife);
	}
	else
	{
		m_IsDead = true;
		Notify(m_pGameObject, GameEvent::Died);
	}
}