#pragma once
#include <string>
#include <vector>

class TileComponent;
class TilePrefab;

class BurgerTimeParser final
{
public:
	BurgerTimeParser() = default;
	~BurgerTimeParser() = default;

	BurgerTimeParser(const BurgerTimeParser& other) = delete;
	BurgerTimeParser(BurgerTimeParser&& other) = delete;
	BurgerTimeParser& operator=(const BurgerTimeParser& other) = delete;
	BurgerTimeParser& operator=(BurgerTimeParser&& other) = delete;

	bool Parse(const std::string& filePath, std::vector<TilePrefab*>& levelTiles);

private:
};