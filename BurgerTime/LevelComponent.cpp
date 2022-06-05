#include "BurgerTimePCH.h"
#include "LevelComponent.h"
#include "BurgerTimeParser.h"
#include "TileComponent.h"
#include "TextureTransformComponent.h"
#include "TransformComponent.h"
#include "RenderComponent.h"
#include "BoxColliderComponent.h"
#include "RigidBodyComponent.h"
#include "BurgerComponent.h"
#include "RenderOrder.h"

LevelComponent::LevelComponent(const std::string& filePath)
	: m_pTiles{}
    , m_IsUpdateNeeded{ true }
{
	BurgerTimeParser parser{};

	if (!parser.Parse(filePath, m_pTiles))
	{
		std::cerr << "Couldn't read level: " + filePath << std::endl;
		return;
	}
}

LevelComponent::~LevelComponent()
{
	for (GameObject* pTile : m_pTiles)
	{
		delete pTile;
		pTile = nullptr;
	}

    for (GameObject* pIngredient : m_pIngredients)
    {
        delete pIngredient;
        pIngredient = nullptr;
    }
}

void LevelComponent::Update()
{
    if (m_IsUpdateNeeded)
    {
        InitializeLevel();

        m_IsUpdateNeeded = false;
    }
}

void LevelComponent::InitializeLevel()
{
    const std::string ingredientSpriteSheet{ "Textures/BurgerTime/Items/Burger.png" };
    const std::string normalSpriteSheet{ "Textures/BurgerTime/Level/Tiles.png" };
    //const std::string alphaSpriteSheet{ "Textures/Level/AlphaTiles.png" };

    int tileSize{ 32 };
    FVec2 startOffset{ GetGameObject()->GetComponent<TransformComponent>()->GetPixelPosition() };
    startOffset.x = startOffset.x - 32.f;
    int xOffset{};
    FVec2 tilePos{};

    TransformComponent* pTfmComp{};
    RigidBodyComponent* pRbyComp{};

    for (size_t idx{}; idx < m_pTiles.size(); ++idx)
    {
        if (int nr{ idx % 11 }; nr % 2 == 1 && nr != 0 && nr != 1)
        {
            xOffset += tileSize;
        }

        if (idx % 11 == 0)
        {
            xOffset = 0;
        }

        tilePos.x = startOffset.x + xOffset + (idx % 11) * tileSize;
        tilePos.y = startOffset.y + (idx / 11) * tileSize;

        pTfmComp = m_pTiles[idx]->AddComponent<TransformComponent>(tilePos.x, tilePos.y);
        m_pTiles[idx]->AddComponent<RenderComponent>(pTfmComp, static_cast<int>(RenderOrder::Level), normalSpriteSheet);
        pRbyComp = m_pTiles[idx]->AddComponent<RigidBodyComponent>(pTfmComp, RigidBodyComponent::BodyType::Static);

        switch (m_pTiles[idx]->GetComponent<TileComponent>()->GetName())
        {
        case TileName::VoidSingle:
            m_pTiles[idx]->AddComponent<TextureTransformComponent>(0, 0, tileSize, tileSize);
            m_pTiles[idx]->AddComponent<BoxColliderComponent>(pRbyComp, 32.f / 16.f, 32.f / 16.f, 16.f / 16.f, 12.f / 16.f);
            break;
        case TileName::VoidDouble:
            m_pTiles[idx]->AddComponent<TextureTransformComponent>(0, 0, tileSize * 2, tileSize);
            m_pTiles[idx]->AddComponent<BoxColliderComponent>(pRbyComp, 64.f / 16.f, 32.f / 16.f, 32.f / 16.f, 12.f / 16.f);
            break;
        case TileName::PlatformSingle:
            m_pTiles[idx]->AddComponent<TextureTransformComponent>(64, 0, tileSize, tileSize);
            m_pTiles[idx]->AddComponent<BoxColliderComponent>(pRbyComp, 32.f / 16.f, 12.f / 16.f, 16.f / 16.f, 2.f / 16.f);
            break;
        case TileName::PlatformSingleStair:
            m_pTiles[idx]->AddComponent<TextureTransformComponent>(96, 0, tileSize, tileSize);
            m_pTiles[idx]->AddComponent<BoxColliderComponent>(pRbyComp, 4.f / 16.f, 12.f / 16.f, 03.f / 16.f, 2.f / 16.f);
            m_pTiles[idx]->AddComponent<BoxColliderComponent>(pRbyComp, 4.f / 16.f, 12.f / 16.f, 30.f / 16.f, 2.f / 16.f);
            break;
        case TileName::PlatformDouble:
            m_pTiles[idx]->AddComponent<TextureTransformComponent>(0, 32, tileSize * 2, tileSize);
            m_pTiles[idx]->AddComponent<BoxColliderComponent>(pRbyComp, 64.f / 16.f, 12.f / 16.f, 32.f / 16.f, 2.f / 16.f);
            break;
        case TileName::PlatformDoubleIngredient:
            m_pTiles[idx]->AddComponent<TextureTransformComponent>(0, 32, tileSize * 2, tileSize);
            m_pTiles[idx]->AddComponent<BoxColliderComponent>(pRbyComp, 64.f / 16.f, 12.f / 16.f, 32.f / 16.f, 2.f / 16.f);
            break;
        case TileName::PlatformDoubleStair:
            m_pTiles[idx]->AddComponent<TextureTransformComponent>(0, 96, tileSize * 2, tileSize);
            m_pTiles[idx]->AddComponent<BoxColliderComponent>(pRbyComp, 20.f / 16.f, 12.f / 16.f, 11.f / 16.f, 2.f / 16.f);
            m_pTiles[idx]->AddComponent<BoxColliderComponent>(pRbyComp, 20.f / 16.f, 12.f / 16.f, 54.f / 16.f, 2.f / 16.f);
            break;
        case TileName::PlatformDoubleStairIngredient:
            m_pTiles[idx]->AddComponent<TextureTransformComponent>(0, 96, tileSize * 2, tileSize);
            m_pTiles[idx]->AddComponent<BoxColliderComponent>(pRbyComp, 20.f / 16.f, 12.f / 16.f, 11.f / 16.f, 2.f / 16.f);
            m_pTiles[idx]->AddComponent<BoxColliderComponent>(pRbyComp, 20.f / 16.f, 12.f / 16.f, 54.f / 16.f, 2.f / 16.f);
            break;
        case TileName::Plate:
            m_pTiles[idx]->AddComponent<TextureTransformComponent>(0, 128, tileSize * 2, tileSize);
            //...
            break;
        case TileName::PlateStart:
            m_pTiles[idx]->AddComponent<TextureTransformComponent>(64, 128, tileSize, tileSize);
            //...
            break;
        case TileName::PlateMiddle:
            m_pTiles[idx]->AddComponent<TextureTransformComponent>(96, 128, tileSize, tileSize);
            //...
            break;
        case TileName::PlateEnd:
            m_pTiles[idx]->AddComponent<TextureTransformComponent>(128, 128, tileSize, tileSize);
            //...
            break;
        case TileName::FloatingSingleStair:
            m_pTiles[idx]->AddComponent<TextureTransformComponent>(128, 0, tileSize, tileSize);
            m_pTiles[idx]->AddComponent<BoxColliderComponent>(pRbyComp, 4.f / 16.f, 32.f / 16.f, 03.f / 16.f, 12.f / 16.f);
            m_pTiles[idx]->AddComponent<BoxColliderComponent>(pRbyComp, 4.f / 16.f, 32.f / 16.f, 30.f / 16.f, 12.f / 16.f);
            break;
        case TileName::FloatingDoubleStair:
            m_pTiles[idx]->AddComponent<TextureTransformComponent>(0, 64, tileSize * 2, tileSize);
            m_pTiles[idx]->AddComponent<BoxColliderComponent>(pRbyComp, 20.f / 16.f, 32.f / 16.f, 11.f / 16.f, 12.f / 16.f);
            m_pTiles[idx]->AddComponent<BoxColliderComponent>(pRbyComp, 20.f / 16.f, 32.f / 16.f, 54.f / 16.f, 12.f / 16.f);
            break;
        case TileName::FloatingSingleStairStart:
            m_pTiles[idx]->AddComponent<TextureTransformComponent>(64, 32, tileSize, tileSize);
            m_pTiles[idx]->AddComponent<BoxColliderComponent>(pRbyComp, 4.f / 16.f, 32.f / 16.f, 03.f / 16.f, 12.f / 16.f);
            m_pTiles[idx]->AddComponent<BoxColliderComponent>(pRbyComp, 4.f / 16.f, 32.f / 16.f, 30.f / 16.f, 12.f / 16.f);
            //...
            break;
        case TileName::FloatingSingleStairMiddle:
            m_pTiles[idx]->AddComponent<TextureTransformComponent>(96, 32, tileSize, tileSize);
            m_pTiles[idx]->AddComponent<BoxColliderComponent>(pRbyComp, 4.f / 16.f, 32.f / 16.f, 03.f / 16.f, 12.f / 16.f);
            m_pTiles[idx]->AddComponent<BoxColliderComponent>(pRbyComp, 4.f / 16.f, 32.f / 16.f, 30.f / 16.f, 12.f / 16.f);
            //...
            break;
        case TileName::FloatingSingleStairEnd:
            m_pTiles[idx]->AddComponent<TextureTransformComponent>(128, 32, tileSize, tileSize);
            m_pTiles[idx]->AddComponent<BoxColliderComponent>(pRbyComp, 4.f / 16.f, 32.f / 16.f, 03.f / 16.f, 12.f / 16.f);
            m_pTiles[idx]->AddComponent<BoxColliderComponent>(pRbyComp, 4.f / 16.f, 32.f / 16.f, 30.f / 16.f, 12.f / 16.f);
            //...
            break;
        case TileName::PlatformSingleStart:
            m_pTiles[idx]->AddComponent<TextureTransformComponent>(64, 96, tileSize, tileSize);
            m_pTiles[idx]->AddComponent<BoxColliderComponent>(pRbyComp, 32.f / 16.f, 12.f / 16.f, 16.f / 16.f, 2.f / 16.f);
            //...
            break;
        case TileName::PlatformSingleMiddle:
            m_pTiles[idx]->AddComponent<TextureTransformComponent>(96, 96, tileSize, tileSize);
            m_pTiles[idx]->AddComponent<BoxColliderComponent>(pRbyComp, 32.f / 16.f, 12.f / 16.f, 16.f / 16.f, 2.f / 16.f);
            //...
            break;
        case TileName::PlatformSingleEnd:
            m_pTiles[idx]->AddComponent<TextureTransformComponent>(128, 96, tileSize, tileSize);
            m_pTiles[idx]->AddComponent<BoxColliderComponent>(pRbyComp, 32.f / 16.f, 12.f / 16.f, 16.f / 16.f, 2.f / 16.f);
            //...
            break;
        case TileName::PlatformSingleStairStart:
            m_pTiles[idx]->AddComponent<TextureTransformComponent>(64, 64, tileSize, tileSize);
            m_pTiles[idx]->AddComponent<BoxColliderComponent>(pRbyComp, 4.f / 16.f, 12.f / 16.f, 03.f / 16.f, 2.f / 16.f);
            m_pTiles[idx]->AddComponent<BoxColliderComponent>(pRbyComp, 4.f / 16.f, 12.f / 16.f, 30.f / 16.f, 2.f / 16.f);
            //...
            break;
        case TileName::PlatformSingleStairMiddle:
            m_pTiles[idx]->AddComponent<TextureTransformComponent>(96, 64, tileSize, tileSize);
            m_pTiles[idx]->AddComponent<BoxColliderComponent>(pRbyComp, 4.f / 16.f, 12.f / 16.f, 03.f / 16.f, 2.f / 16.f);
            m_pTiles[idx]->AddComponent<BoxColliderComponent>(pRbyComp, 4.f / 16.f, 12.f / 16.f, 30.f / 16.f, 2.f / 16.f);
            //...
            break;
        case TileName::PlatformSingleStairEnd:
            m_pTiles[idx]->AddComponent<TextureTransformComponent>(128, 64, tileSize, tileSize);
            m_pTiles[idx]->AddComponent<BoxColliderComponent>(pRbyComp, 4.f / 16.f, 12.f / 16.f, 03.f / 16.f, 2.f / 16.f);
            m_pTiles[idx]->AddComponent<BoxColliderComponent>(pRbyComp, 4.f / 16.f, 12.f / 16.f, 30.f / 16.f, 2.f / 16.f);
            //...
            break;
        default:
            break;
        }

        GetGameObject()->AddChild(m_pTiles[idx]);

        Ingredient ingredient{ m_pTiles[idx]->GetComponent<TileComponent>()->GetIngredient() };

        if (ingredient == Ingredient::None)
        {
            continue;
        }

        GameObject* pIngredient{ m_pIngredients.emplace_back(new GameObject{}) };
        constexpr float ingredientOffset{ 16.f };

        pTfmComp = pIngredient->AddComponent<TransformComponent>(tilePos.x, tilePos.y + ingredientOffset);
        pIngredient->AddComponent<BurgerComponent>(pTfmComp, ingredient, ingredientSpriteSheet);

        GetGameObject()->AddChild(pIngredient);
    }
}