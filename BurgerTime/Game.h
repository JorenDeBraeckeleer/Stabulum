#pragma once

#include "GameObject.h"
#include "Stabulum.h"

class Game final : public Stabulum
{
public:
	Game() = default;
	~Game() = default;

	Game(const Game&) = delete;
	Game(Game&&) = delete;
	Game& operator= (const Game&) = delete;
	Game& operator= (const Game&&) = delete;

	void Initialize();
	void LoadGame();
	void Cleanup();
	void Run();

private:
	void HighScore();

	void LoadLevel(const std::string& levelFile, const int levelIndex, int highScore);

	std::vector<GameObject*> m_pPeterPeppers{};
	std::vector<GameObject*> m_pLevels{};

	FVec2 m_LevelSize{ 416.f, 400.f};
	float m_Border{ 16.f };
};