#pragma once

#include "BaseComponent.h"

enum class TileName
{
	VoidSingle = 160,
	VoidDouble = 260,
	PlatformSingle = 100,
	PlatformSingleStair = 110,
	PlatformDouble = 200,
	PlatformDoubleIngredient = 209,
	PlatformDoubleStair = 210,
	PlatformDoubleStairIngredient = 219,
	Plate = 300,
	PlateStart = 304,
	PlateMiddle = 305,
	PlateEnd = 306,
	FloatingSingleStair = 710,
	FloatingDoubleStair = 810,
	FloatingSingleStairStart = 714,
	FloatingSingleStairMiddle = 715,
	FloatingSingleStairEnd = 716,
	PlatformSingleStart = 104,
	PlatformSingleMiddle = 105,
	PlatformSingleEnd = 106,
	PlatformSingleStairStart = 114,
	PlatformSingleStairMiddle = 115,
	PlatformSingleStairEnd = 116,
};

enum class Ingredient
{
	None = -1,
	BunBottom = 0,
	BunTop = 1,
	Cheese = 2,
	Lettuce = 3,
	Meat = 4,
	Tomato = 5,
};

class TileComponent final : public BaseComponent
{
public:
	TileComponent();
	~TileComponent() = default;

	TileComponent(const TileComponent& other) = delete;
	TileComponent(TileComponent&& other) = delete;
	TileComponent& operator=(const TileComponent& other) = delete;
	TileComponent& operator=(TileComponent&& other) = delete;

	virtual void Update() override;

	void SetName(const TileName& tileName) { m_Name = tileName; }
	TileName GetName() { return m_Name; }
	void SetIngredient(const Ingredient& ingredient) { m_Ingredient = ingredient; }
	Ingredient GetIngredient() { return m_Ingredient; }

private:
	TileName m_Name;
	Ingredient m_Ingredient;
};