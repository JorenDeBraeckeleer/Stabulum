#pragma once

#include "SoundManager.h"

class ServiceLocator final
{
public:
    static void RegisterSoundManager(SoundManager* pSoundManager);
    static SoundManager* GetSoundManager() { return m_pSoundManager; }

private:
    ServiceLocator() = delete;
    ~ServiceLocator() = delete;

    ServiceLocator(const ServiceLocator& other) = delete;
    ServiceLocator(ServiceLocator&& other) noexcept = delete;
    ServiceLocator& operator=(const ServiceLocator& other) = delete;
    ServiceLocator& operator=(ServiceLocator&& other) noexcept = delete;

    static SoundManager* m_pSoundManager;
    static NullSoundManager m_DefaultSoundManager;
};