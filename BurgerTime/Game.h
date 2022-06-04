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
	GameObject* m_pWall6{ new GameObject{} };
	GameObject* m_pWall5{ new GameObject{} };
	GameObject* m_pWall4{ new GameObject{} };
	GameObject* m_pWall3{ new GameObject{} };
};