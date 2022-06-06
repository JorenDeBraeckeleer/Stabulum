#pragma once

#include "Stabulum.h"

#include "GameObject.h"

class Game final : public Stabulum
{
public:
	void Initialize();
	void LoadGame();
	void Cleanup();
	void Run();

private:
	void HighScore();

	void LoadTestScene() const;
	void LoadLevel(const std::string& levelFile, const int levelIndex, int highScore);

	std::vector<GameObject*> m_pPeterPeppers{};
	//GameObject* m_pPeterPepper{ new GameObject{} };
	std::vector<GameObject*> m_pLevels{};
	//GameObject* m_pLevel{ new GameObject{} };

	FVec2 m_LevelSize{ 416.f, 400.f};
	float m_Border{ 16.f };
};