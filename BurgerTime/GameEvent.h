#pragma once

enum class GameEvent
{
	//Initialize
	UpdateLives = 0,

	//Character
	LostLife = 10,
	Died = 11,

	//InGame
	BurgerDropped = 20,
	EnemyDied = 21,
};