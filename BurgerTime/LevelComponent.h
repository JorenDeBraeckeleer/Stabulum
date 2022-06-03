#pragma once
#include "BaseComponent.h"

class TileComponent;

class LevelComponent final : public BaseComponent
{
public:
	LevelComponent(const std::string& filePath);
	~LevelComponent();

	LevelComponent(const LevelComponent& other) = delete;
	LevelComponent(LevelComponent&& other) = delete;
	LevelComponent& operator=(const LevelComponent& other) = delete;
	LevelComponent& operator=(LevelComponent&& other) = delete;

	virtual void Update() override;

private:
	void InitializeLevel();

	std::vector<GameObject*> m_pTiles;

	bool m_IsUpdateNeeded;
};