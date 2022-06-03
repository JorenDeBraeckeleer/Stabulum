#include "BurgerTimePCH.h"
#include "BurgerTimeParser.h"

#include <fstream>

#include "TileComponent.h"
#include "TilePrefab.h"

bool BurgerTimeParser::Parse(const std::string& filePath, std::vector<TilePrefab*>& levelTiles)
{
	//Open file
	std::ifstream file(filePath);

	if (!file.is_open())
	{
		return false;
	}

	std::vector<int> ingredients{};

	std::string command{};

	//Read whole file
	while (!file.eof())
	{
		file >> command;

		if (command == "#")
		{
			//A comment, do nothing
		}
		else if (command == "i")
		{
			//Ingredient
			std::getline(file, command);

			for (char& c : command)
			{
				if (c != ' ')
				{
					ingredients.emplace_back(int(c - '0'));
				}
			}

			std::reverse(ingredients.begin(), ingredients.end());
		}
		else if (command == "l")
		{
			//Level
			std::getline(file, command);

			for (size_t idx{}; idx < command.size() - 2; ++idx)
			{
				if (command[idx] != ' ')
				{
					int name{ int(command[idx] - '0') * 100 }, stair{ int(command[idx + 1] - '0') * 10 }, ingredient{ int(command[idx + 2] - '0') };
					int nr{ name + stair + ingredient };

					TilePrefab* pTile{ new TilePrefab{} };
					pTile->SetName(static_cast<TileName>(nr));

					if (ingredient == 9)
					{
						pTile->SetIngredient(static_cast<Ingredient>(ingredients.back()));
						ingredients.pop_back();
					}

					levelTiles.emplace_back(pTile);

					idx += 2;
				}
			}
		}
	}

	return true;
}