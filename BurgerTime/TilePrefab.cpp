#include "BurgerTimePCH.h"
#include "TilePrefab.h"

TilePrefab::TilePrefab()
	: GameObject()
	, m_Name{ TileName::VoidSingle }
	, m_Ingredient{ Ingredient::None }
{
}