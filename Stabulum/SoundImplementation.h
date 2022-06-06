#pragma once

class SoundImplementation final
{
public:
	SoundImplementation();
	~SoundImplementation();

	SoundImplementation(const SoundImplementation& other) = delete;
	SoundImplementation(SoundImplementation&& other) noexcept = delete;
	SoundImplementation& operator=(const SoundImplementation& other) = delete;
	SoundImplementation& operator=(SoundImplementation&& other) noexcept = delete;

	bool Play(unsigned short id, const int volume, bool doesLoop);
	void Load(const std::string& filePath, unsigned short id);

private:
	class Implementation;
	Implementation* m_pImpl;
};