#include "BurgerTimePCH.h"
#include "BurgerTimeParser.h"

#include <fstream>

#include "GameObject.h"
#include "TileComponent.h"

bool BurgerTimeParser::Parse(const std::string& filePath, std::vector<GameObject*>& levelTiles, FVec2& playerPosition)
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
			GameObject* pStartTile{ new GameObject{} };
			TileComponent* pStartComp = pStartTile->AddComponent<TileComponent>();
			pStartComp->SetName(TileName::VoidSingle);
			levelTiles.emplace_back(pStartTile);

			std::getline(file, command);

			for (size_t idx{}; idx < command.size() - 2; ++idx)
			{
				if (command[idx] != ' ')
				{
					int name{ int(command[idx] - '0') * 100 }, stair{ int(command[idx + 1] - '0') * 10 }, ingredient{ int(command[idx + 2] - '0') };
					int nr{ name + stair + ingredient };

					GameObject* pTile{ new GameObject{} };
					TileComponent* pComp = pTile->AddComponent<TileComponent>();
					
					pComp->SetName(static_cast<TileName>(nr));					

					if (ingredient == 9)
					{
						pComp->SetIngredient(static_cast<Ingredient>(ingredients.back()));
						ingredients.pop_back();
					}

					levelTiles.emplace_back(pTile);

					idx += 2;
				}
			}

			GameObject* pEndTile{ new GameObject{} };
			TileComponent* pEndComp = pEndTile->AddComponent<TileComponent>();
			pEndComp->SetName(TileName::VoidSingle);
			levelTiles.emplace_back(pEndTile);
		}
		else if (command == "p")
		{
			float x{}, y{};
			file >> x >> y;
			x = x * 32.f + int(x / 2) * 32.f;
			y *= 32.f;
			playerPosition = FVec2{ x - 8.f, y };
		}
	}

	return true;
}