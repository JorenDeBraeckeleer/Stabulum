#pragma once

using SoundId = unsigned short;

//This is not the real pImpl, this class can be foward declared here
class SoundImplementation;

class SoundManager
{
public:
    SoundManager();
    virtual ~SoundManager() = default;

    SoundManager(const SoundManager& other) = delete;
    SoundManager(SoundManager&& other) noexcept = delete;
    SoundManager& operator=(const SoundManager& other) = delete;
    SoundManager& operator=(SoundManager&& other) noexcept = delete;

    void Init(const std::string& dataPath);

    virtual bool Play(SoundId id, const int volume = 1, bool doesLoop = false) = 0;
    virtual void Load(const std::string& filePath, SoundId id) = 0;

    void SetBackgroundMusicPlaying(bool isPlaying = true) { m_IsBackgroundMusicPlaying = isPlaying; }
    bool GetBackgroundMusicPlaying() { return m_IsBackgroundMusicPlaying; }

protected:
    std::string m_DataPath;
    bool m_IsBackgroundMusicPlaying;
};

class NullSoundManager final : public SoundManager
{
public:
    NullSoundManager() = default;
    virtual ~NullSoundManager() override = default;

    virtual bool Play(SoundId, const int, bool) override { return false; }
    virtual void Load(const std::string&, SoundId) override {  }
};

class SDLSoundManager final : public SoundManager
{
public:
    SDLSoundManager();
    virtual ~SDLSoundManager() override;

    virtual bool Play(SoundId id, const int volume = 1, bool doesLoop = false) override;
    virtual void Load(const std::string& filePath, SoundId id) override;

private:
    SoundImplementation* m_pImpl;
};

class LoggingSoundManager final : public SoundManager
{
public:
    LoggingSoundManager(SoundManager* pSoundManager);
    virtual ~LoggingSoundManager() override;

    virtual bool Play(SoundId id, const int volume = 1, bool doesLoop = false) override;
    virtual void Load(const std::string& filePath, SoundId id) override;

    std::string GetPathTest() { return m_DataPath; }

private:
    SoundManager* m_pSoundManager;
};