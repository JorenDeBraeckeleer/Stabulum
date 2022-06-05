#include "StabulumPCH.h"
#include "SoundManager.h"

#include "SoundImplementation.h"

SoundManager::SoundManager()
	: m_DataPath{}
{
}

void SoundManager::Init(const std::string& dataPath)
{
	m_DataPath = dataPath;
}

SDLSoundManager::SDLSoundManager()
	: SoundManager{}
	, m_pImpl{ new SoundImplementation{} }
{
}

SDLSoundManager::~SDLSoundManager()
{
	delete m_pImpl;
	m_pImpl = nullptr;
}

bool SDLSoundManager::Play(SoundId id, const int volume, bool doesLoop)
{
	return m_pImpl->Play(id, volume, doesLoop);
}

void SDLSoundManager::Load(const std::string& filePath, SoundId id)
{
	m_pImpl->Load(m_DataPath + filePath, id);
}

LoggingSoundManager::LoggingSoundManager(SoundManager* pSoundManager)
	: SoundManager{}
	, m_pSoundManager{ pSoundManager }
{
}

LoggingSoundManager::~LoggingSoundManager()
{
	delete m_pSoundManager;
	m_pSoundManager = nullptr;
}

bool LoggingSoundManager::Play(SoundId id, const int volume, bool doesLoop)
{
	if (m_pSoundManager->Play(id, volume, doesLoop))
	{
		std::cout << "Playing sound." << std::endl;
		return true;
	}

	return false;
}

void LoggingSoundManager::Load(const std::string& filePath, SoundId id)
{
	std::cout << "Checking and loading sound: " << m_DataPath + filePath << std::endl;
	m_pSoundManager->Load(m_DataPath + filePath, id);
}