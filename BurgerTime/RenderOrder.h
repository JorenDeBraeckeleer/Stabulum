#pragma once

enum class RenderOrder
{
	//Render first (bottom)
	Level = 0,
	Burger = 1,
	Enemy = 2,
	Player = 3,
	HUD = 4,
	UI = 5,
	//Render last (top)

	//Amount of layers
	Amount = 6,
};