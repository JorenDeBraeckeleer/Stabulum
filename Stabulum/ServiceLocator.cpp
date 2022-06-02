#include "StabulumPCH.h"
#include "ServiceLocator.h"

NullSoundManager ServiceLocator::m_DefaultSoundManager;
SoundManager* ServiceLocator::m_pSoundManager = &ServiceLocator::m_DefaultSoundManager;

void ServiceLocator::RegisterSoundManager(SoundManager* pSoundManager)
{
	if (m_pSoundManager != &m_DefaultSoundManager)
	{
		delete m_pSoundManager;
		m_pSoundManager = nullptr;
	}

	m_pSoundManager = pSoundManager == nullptr ? &m_DefaultSoundManager : pSoundManager;
}