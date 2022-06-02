#include "StabulumPCH.h"
#include "SoundImplementation.h"

#include <mutex>
#include <queue>
#include <thread>
#include <set>

#include "SDL_mixer.h"

class SoundClip final
{
public:
    SoundClip(const std::string& filePath, unsigned short id)
        : m_FilePath{ filePath }
        , m_pChunk{ nullptr }
        , m_Id{ id }
    {
    }

    ~SoundClip()
    {
        if (m_pChunk)
        {
            Mix_FreeChunk(m_pChunk);
        }
    }

    SoundClip(const SoundClip& other) = delete;
    SoundClip(SoundClip&& other) noexcept = delete;
    SoundClip& operator=(const SoundClip& other) = delete;
    SoundClip& operator=(SoundClip&& other) noexcept = delete;

    void Play()
    {
        if (!IsLoaded())
        {
            return;
        }

        Mix_PlayChannel(-1, m_pChunk, 0);
    }

    void SetVolume(int volume)
    {
        if (IsLoaded())
        {
            Mix_VolumeChunk(m_pChunk, volume);
        }
    }

    void Load()
    {
        if (IsLoaded())
        {
            return;
        }

        m_pChunk = Mix_LoadWAV(m_FilePath.c_str());

        if (!m_pChunk)
        {
            std::cerr << "Audioclip " << m_FilePath << " failed to load, SDL_mixer error: " << Mix_GetError() << std::endl;
        }
    }

    bool IsLoaded() const
    {
        return m_pChunk != nullptr;
    }

    const unsigned short GetId() { return m_Id; }
    const std::string GetFilePath() { return m_FilePath; }

private:
    const std::string m_FilePath;
    Mix_Chunk* m_pChunk;
    unsigned short m_Id;
};

class SoundImplementation::Implementation final
{
public:
    Implementation()
    {
        //Open audio
        Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 512);

        //Start sound thread
        m_SoundThread = std::thread(&Implementation::SoundLoop, this);
    }

    ~Implementation()
    {
        //Close audio
        Mix_CloseAudio();

        {
            //Lock bool
            std::lock_guard<std::mutex> lg(m_SoundMutex);

            //Prepare to quit sound thread
            m_Quit = true;

            //Delete sounds
            for (auto x : m_pSounds)
            {
                delete x;
                x = nullptr;
            }
        }

        //Notify sound thread
        m_SoundQueueConditionVariable.notify_all();

        //Finish sound thread
        m_SoundThread.join();
    }

    Implementation(const Implementation& other) = delete;
    Implementation(Implementation&& other) noexcept = delete;
    Implementation& operator=(const Implementation& other) = delete;
    Implementation& operator=(Implementation&& other) noexcept = delete;

    bool Play(unsigned short id, const int volume)
    {
        {
            //Lock queue
            std::lock_guard<std::mutex> lg(m_SoundMutex);

            //Find sound clip
            if (m_Ids.contains(id))
            {
                for (SoundClip* pClip : m_pSounds)
                {
                    if (pClip->GetId() == id)
                    {
                        pClip->SetVolume(volume);
                        m_pPlayQueue.push(pClip);
                    }
                }
            }
            else
            {
                std::cout << "No sound with this id has been found." << std::endl;
                return false;
            }
        }

        //Notify sound thread
        m_SoundQueueConditionVariable.notify_all();

        return true;
    }

    void Load(const std::string& filePath, unsigned short id)
    {
        {
            //Lock queue
            std::lock_guard<std::mutex> lg(m_SoundMutex);

            //Unique id check
            if (m_Ids.contains(id))
            {
                return;
            }
            else
            {
                m_Ids.insert(id);
            }

            //Add sound clip
            m_pLoadQueue.push(new SoundClip{ filePath, id });
        }

        //Notify sound thread
        m_SoundQueueConditionVariable.notify_all();
    }

private:
    void SoundLoop()
    {
        while (true)
        {
            //Wait for calls
            std::unique_lock<std::mutex> lock(m_SoundMutex);
            m_SoundQueueConditionVariable.wait(lock, [&]() { return !m_pLoadQueue.empty() || !m_pPlayQueue.empty() || m_Quit; });

            //Check to quit/continue
            if (m_Quit)
            {
                break;
            }

            //Spurious wakeup check
            if (!m_pPlayQueue.empty())
            {
                //Get clip, check load, play it
                SoundClip* pClip = m_pPlayQueue.front();

                //Delete sound from queue
                m_pPlayQueue.pop();

                //Unlock the lock
                lock.unlock();

                //Do stuff
                pClip->Load();
                pClip->Play();
            }
            else if (!m_pLoadQueue.empty())
            {
                //Get clip, load it
                SoundClip* pClip = m_pLoadQueue.front();

                //Delete sound from queue
                m_pLoadQueue.pop();

                //Unlock the lock
                lock.unlock();

                //Do stuff
                pClip->Load();

                //Add to sounds
                m_pSounds.push_back(pClip);
            }
        }
    }

    std::thread m_SoundThread;
    std::mutex m_SoundMutex;

    std::queue<SoundClip*> m_pPlayQueue;
    std::queue<SoundClip*> m_pLoadQueue;
    std::vector<SoundClip*> m_pSounds;
    std::set<unsigned short> m_Ids;

    std::condition_variable m_SoundQueueConditionVariable;
    bool m_Quit = false;
};

SoundImplementation::SoundImplementation()
    : m_pImpl{ new Implementation{} }
{
}

SoundImplementation::~SoundImplementation()
{
    delete m_pImpl;
    m_pImpl = nullptr;
}

bool SoundImplementation::Play(unsigned short id, const int volume)
{
    return m_pImpl->Play(id, volume);
}

void SoundImplementation::Load(const std::string& filePath, unsigned short id)
{
    m_pImpl->Load(filePath, id);
}