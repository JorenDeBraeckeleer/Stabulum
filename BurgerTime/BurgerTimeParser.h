#pragma once
#include <string>
#include <vector>

enum class TileNames
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
};

enum class Ingredients
{
	None = -1,
	BunBottom = 0,
	BunTop = 1,
	Cheese = 2,
	Lettuce = 3,
	Meat = 4,
	Tomato = 5,
};

struct Tile
{
	TileNames Name = TileNames::FloatingSingleStairMiddle;
	Ingredients Ingredient = Ingredients::None;
};

class BurgerTimeParser final
{
public:
	BurgerTimeParser() = default;
	~BurgerTimeParser() = default;

	BurgerTimeParser(const BurgerTimeParser& other) = delete;
	BurgerTimeParser(BurgerTimeParser&& other) = delete;
	BurgerTimeParser& operator=(const BurgerTimeParser& other) = delete;
	BurgerTimeParser& operator=(BurgerTimeParser&& other) = delete;

	void SetInputFile(const std::string& file) { m_FilePath = file; }
	bool Parse(std::vector<Tile>& level);

private:
	std::string m_FilePath;
};