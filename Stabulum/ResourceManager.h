#pragma once

#include "Singleton.h"

class Font;
class Texture2D;

class ResourceManager final : public Singleton<ResourceManager>
{
public:
	~ResourceManager() = default;

	ResourceManager(const ResourceManager&) = delete;
	ResourceManager(ResourceManager&&) = delete;
	ResourceManager& operator= (const ResourceManager&) = delete;
	ResourceManager& operator= (const ResourceManager&&) = delete;

	void Init(const std::string& data);
	std::shared_ptr<Texture2D> LoadTexture(const std::string& file) const;
	std::shared_ptr<Font> LoadFont(const std::string& file, unsigned int size) const;

private:
	friend class Singleton<ResourceManager>;
	ResourceManager() = default;

	std::string m_DataPath;
};