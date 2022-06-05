#pragma once

class SoundImplementation final
{
public:
	SoundImplementation();
	~SoundImplementation();

	bool Play(unsigned short id, const int volume, bool doesLoop);
	void Load(const std::string& filePath, unsigned short id);

private:
	class Implementation;
	Implementation* m_pImpl;
};