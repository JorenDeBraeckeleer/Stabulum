#pragma once

#include "Stabulum.h"

#include "GameObject.h"

class Game final : public Stabulum
{
public:
	void Initialize();
	void LoadGame() const;
	void Cleanup();
	void Run();

private:
	void LoadTestScene() const;
	void LoadLevel1() const;

	GameObject* m_pPeterPepper{ new GameObject{} };
	GameObject* m_pLevel{ new GameObject{} };

	FVec2 m_LevelSize{ 416.f, 400.f};
	float m_Border{ 16.f };
};