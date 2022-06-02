#pragma once

#include "Stabulum.h"

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
};