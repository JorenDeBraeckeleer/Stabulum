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
#include "BurgerPlatformComponent.h"
#include "RenderOrder.h"
#include "Scene.h"
#include "ScoreComponent.h"
#include "ServiceLocator.h"

LevelComponent::LevelComponent(const std::string& filePath)
	: m_pTiles{}
    , m_PlayerPosition{}
    , m_Completed{}
    , m_IsUpdateNeeded{ true }
{
	BurgerTimeParser parser{};

	if (!parser.Parse(filePath, m_pTiles, m_PlayerPosition))
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

    //Play background music
    if (SoundManager* pSM = ServiceLocator::GetSoundManager(); !pSM->GetBackgroundMusicPlaying())
    {
        pSM->SetBackgroundMusicPlaying();

        pSM->Play(10, 5, true);
    }

    for (size_t idx{}; idx < m_pIngredients.size(); ++idx)
    {
        if (!m_pIngredients[idx]->GetComponent<BurgerComponent>()->GetIsOverlapping())
        {
            return;
        }

        if (idx == m_pIngredients.size() - 1 && !m_Completed)
        {
            m_Completed = true;

            //Update scene and score
            int score = GetGameObject()->GetScene()->FindComponent<ScoreComponent>()->GetScore();

            SceneManager& sceneManager = SceneManager::GetInstance();
            sceneManager.LoadNextScene();
            sceneManager.GetActiveScene()->FindComponent<ScoreComponent>()->SetScore(score);
        }
    }
}

void LevelComponent::InitializeLevel()
{
    const std::string ingredientSpriteSheet{ "Textures/BurgerTime/Items/Burger.png" };
    const std::string normalSpriteSheet{ "Textures/BurgerTime/Level/Tiles.png" };
    //const std::string alphaSpriteSheet{ "Textures/Level/AlphaTiles.png" };

    int tileSize{ 32 };
    FVec2 startOffset{ GetGameObject()->GetComponent<TransformComponent>()->GetWorldPosition() };
    int xOffset{};
    FVec2 tilePos{};
    int levelCollisionGroup{ static_cast<int>(ColliderComponent::CollisionGroup::Level) };
    int burgerCollisionGroup{ static_cast<int>(ColliderComponent::CollisionGroup::Burger) };

    TransformComponent* pTfmComp{};
    RigidBodyComponent* pRbyComp{};
    BoxColliderComponent* pBcd{};
    BurgerPlatformComponent* pBrp{};

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
            m_pTiles[idx]->AddComponent<BoxColliderComponent>(pRbyComp, 32.f / 16.f, 32.f / 16.f, 16.f / 16.f, 12.f / 16.f, 0.f, levelCollisionGroup);
            break;
        case TileName::VoidDouble:
            m_pTiles[idx]->AddComponent<TextureTransformComponent>(0, 0, tileSize * 2, tileSize);
            m_pTiles[idx]->AddComponent<BoxColliderComponent>(pRbyComp, 64.f / 16.f, 32.f / 16.f, 32.f / 16.f, 12.f / 16.f, 0.f, levelCollisionGroup);
            break;
        case TileName::PlatformSingle:
            m_pTiles[idx]->AddComponent<TextureTransformComponent>(64, 0, tileSize, tileSize);
            m_pTiles[idx]->AddComponent<BoxColliderComponent>(pRbyComp, 32.f / 16.f, 12.f / 16.f, 16.f / 16.f, 2.f / 16.f, 0.f, levelCollisionGroup);
            break;
        case TileName::PlatformSingleStair:
            m_pTiles[idx]->AddComponent<TextureTransformComponent>(96, 0, tileSize, tileSize);
            m_pTiles[idx]->AddComponent<BoxColliderComponent>(pRbyComp, 4.f / 16.f, 12.f / 16.f, 03.f / 16.f, 2.f / 16.f, 0.f, levelCollisionGroup);
            m_pTiles[idx]->AddComponent<BoxColliderComponent>(pRbyComp, 4.f / 16.f, 12.f / 16.f, 30.f / 16.f, 2.f / 16.f, 0.f, levelCollisionGroup);
            break;
        case TileName::PlatformDouble:
            m_pTiles[idx]->AddComponent<TextureTransformComponent>(0, 32, tileSize * 2, tileSize);
            m_pTiles[idx]->AddComponent<BoxColliderComponent>(pRbyComp, 64.f / 16.f, 12.f / 16.f, 32.f / 16.f, 2.f / 16.f, 0.f, levelCollisionGroup);
            pBcd = m_pTiles[idx]->AddComponent<BoxColliderComponent>(pRbyComp, 32.f / 16.f, 1.f / 16.f, 16.f / 16.f, 26.f / 16.f, 0.f, burgerCollisionGroup);
            pBrp = m_pTiles[idx]->AddComponent<BurgerPlatformComponent>();
            pBcd->SetSensor();
            pBcd->OnTriggerEnter = std::bind(&BurgerPlatformComponent::OnTriggerEnter, pBrp, std::placeholders::_1);
            pBcd->OnTriggerExit = std::bind(&BurgerPlatformComponent::OnTriggerExit, pBrp, std::placeholders::_1);
            break;
        case TileName::PlatformDoubleIngredient:
            m_pTiles[idx]->AddComponent<TextureTransformComponent>(0, 32, tileSize * 2, tileSize);
            m_pTiles[idx]->AddComponent<BoxColliderComponent>(pRbyComp, 64.f / 16.f, 12.f / 16.f, 32.f / 16.f, 2.f / 16.f, 0.f, levelCollisionGroup);
            pBcd = m_pTiles[idx]->AddComponent<BoxColliderComponent>(pRbyComp, 32.f / 16.f, 1.f / 16.f, 16.f / 16.f, 26.f / 16.f, 0.f, burgerCollisionGroup);
            pBrp = m_pTiles[idx]->AddComponent<BurgerPlatformComponent>();
            pBcd->SetSensor();
            pBcd->OnTriggerEnter = std::bind(&BurgerPlatformComponent::OnTriggerEnter, pBrp, std::placeholders::_1);
            pBcd->OnTriggerExit = std::bind(&BurgerPlatformComponent::OnTriggerExit, pBrp, std::placeholders::_1);
            break;
        case TileName::PlatformDoubleStair:
            m_pTiles[idx]->AddComponent<TextureTransformComponent>(0, 96, tileSize * 2, tileSize);
            m_pTiles[idx]->AddComponent<BoxColliderComponent>(pRbyComp, 20.f / 16.f, 12.f / 16.f, 11.f / 16.f, 2.f / 16.f, 0.f, levelCollisionGroup);
            m_pTiles[idx]->AddComponent<BoxColliderComponent>(pRbyComp, 20.f / 16.f, 12.f / 16.f, 54.f / 16.f, 2.f / 16.f, 0.f, levelCollisionGroup);
            pBcd = m_pTiles[idx]->AddComponent<BoxColliderComponent>(pRbyComp, 32.f / 16.f, 1.f / 16.f, 16.f / 16.f, 26.f / 16.f, 0.f, burgerCollisionGroup);
            pBrp = m_pTiles[idx]->AddComponent<BurgerPlatformComponent>();
            pBcd->SetSensor();
            pBcd->OnTriggerEnter = std::bind(&BurgerPlatformComponent::OnTriggerEnter, pBrp, std::placeholders::_1);
            pBcd->OnTriggerExit = std::bind(&BurgerPlatformComponent::OnTriggerExit, pBrp, std::placeholders::_1);
            break;
        case TileName::PlatformDoubleStairIngredient:
            m_pTiles[idx]->AddComponent<TextureTransformComponent>(0, 96, tileSize * 2, tileSize);
            m_pTiles[idx]->AddComponent<BoxColliderComponent>(pRbyComp, 20.f / 16.f, 12.f / 16.f, 11.f / 16.f, 2.f / 16.f, 0.f, levelCollisionGroup);
            m_pTiles[idx]->AddComponent<BoxColliderComponent>(pRbyComp, 20.f / 16.f, 12.f / 16.f, 54.f / 16.f, 2.f / 16.f, 0.f, levelCollisionGroup);
            pBcd = m_pTiles[idx]->AddComponent<BoxColliderComponent>(pRbyComp, 32.f / 16.f, 1.f / 16.f, 16.f / 16.f, 26.f / 16.f, 0.f, burgerCollisionGroup);
            pBrp = m_pTiles[idx]->AddComponent<BurgerPlatformComponent>();
            pBcd->SetSensor();
            pBcd->OnTriggerEnter = std::bind(&BurgerPlatformComponent::OnTriggerEnter, pBrp, std::placeholders::_1);
            pBcd->OnTriggerExit = std::bind(&BurgerPlatformComponent::OnTriggerExit, pBrp, std::placeholders::_1);
            break;
        case TileName::Plate:
            m_pTiles[idx]->AddComponent<TextureTransformComponent>(0, 128, tileSize * 2, tileSize);
            m_pTiles[idx]->AddComponent<BoxColliderComponent>(pRbyComp, 64.f / 16.f, 32.f / 16.f, 32.f / 16.f, 12.f / 16.f, 0.f, levelCollisionGroup);
            m_pTiles[idx]->AddComponent<BoxColliderComponent>(pRbyComp, 32.f / 16.f, 8.f / 16.f, 16.f / 16.f, 10.f / 16.f, 0.f, burgerCollisionGroup);
            //...
            break;
        case TileName::PlateStart:
            m_pTiles[idx]->AddComponent<TextureTransformComponent>(64, 128, tileSize, tileSize);
            m_pTiles[idx]->AddComponent<BoxColliderComponent>(pRbyComp, 32.f / 16.f, 32.f / 16.f, 16.f / 16.f, 12.f / 16.f, 0.f, levelCollisionGroup);
            //...
            break;
        case TileName::PlateMiddle:
            m_pTiles[idx]->AddComponent<TextureTransformComponent>(96, 128, tileSize, tileSize);
            m_pTiles[idx]->AddComponent<BoxColliderComponent>(pRbyComp, 32.f / 16.f, 32.f / 16.f, 16.f / 16.f, 12.f / 16.f, 0.f, levelCollisionGroup);
            //...
            break;
        case TileName::PlateEnd:
            m_pTiles[idx]->AddComponent<TextureTransformComponent>(128, 128, tileSize, tileSize);
            m_pTiles[idx]->AddComponent<BoxColliderComponent>(pRbyComp, 32.f / 16.f, 32.f / 16.f, 16.f / 16.f, 12.f / 16.f, 0.f, levelCollisionGroup);
            //...
            break;
        case TileName::FloatingSingleStair:
            m_pTiles[idx]->AddComponent<TextureTransformComponent>(128, 0, tileSize, tileSize);
            m_pTiles[idx]->AddComponent<BoxColliderComponent>(pRbyComp, 4.f / 16.f, 32.f / 16.f, 03.f / 16.f, 12.f / 16.f, 0.f, levelCollisionGroup);
            m_pTiles[idx]->AddComponent<BoxColliderComponent>(pRbyComp, 4.f / 16.f, 32.f / 16.f, 30.f / 16.f, 12.f / 16.f, 0.f, levelCollisionGroup);
            break;
        case TileName::FloatingDoubleStair:
            m_pTiles[idx]->AddComponent<TextureTransformComponent>(0, 64, tileSize * 2, tileSize);
            m_pTiles[idx]->AddComponent<BoxColliderComponent>(pRbyComp, 20.f / 16.f, 32.f / 16.f, 11.f / 16.f, 12.f / 16.f, 0.f, levelCollisionGroup);
            m_pTiles[idx]->AddComponent<BoxColliderComponent>(pRbyComp, 20.f / 16.f, 32.f / 16.f, 54.f / 16.f, 12.f / 16.f, 0.f, levelCollisionGroup);
            break;
        case TileName::FloatingSingleStairStart:
            m_pTiles[idx]->AddComponent<TextureTransformComponent>(64, 32, tileSize, tileSize);
            m_pTiles[idx]->AddComponent<BoxColliderComponent>(pRbyComp, 4.f / 16.f, 32.f / 16.f, 03.f / 16.f, 12.f / 16.f, 0.f, levelCollisionGroup);
            m_pTiles[idx]->AddComponent<BoxColliderComponent>(pRbyComp, 4.f / 16.f, 32.f / 16.f, 30.f / 16.f, 12.f / 16.f, 0.f, levelCollisionGroup);
            //...
            break;
        case TileName::FloatingSingleStairMiddle:
            m_pTiles[idx]->AddComponent<TextureTransformComponent>(96, 32, tileSize, tileSize);
            m_pTiles[idx]->AddComponent<BoxColliderComponent>(pRbyComp, 4.f / 16.f, 32.f / 16.f, 03.f / 16.f, 12.f / 16.f, 0.f, levelCollisionGroup);
            m_pTiles[idx]->AddComponent<BoxColliderComponent>(pRbyComp, 4.f / 16.f, 32.f / 16.f, 30.f / 16.f, 12.f / 16.f, 0.f, levelCollisionGroup);
            //...
            break;
        case TileName::FloatingSingleStairEnd:
            m_pTiles[idx]->AddComponent<TextureTransformComponent>(128, 32, tileSize, tileSize);
            m_pTiles[idx]->AddComponent<BoxColliderComponent>(pRbyComp, 4.f / 16.f, 32.f / 16.f, 03.f / 16.f, 12.f / 16.f, 0.f, levelCollisionGroup);
            m_pTiles[idx]->AddComponent<BoxColliderComponent>(pRbyComp, 4.f / 16.f, 32.f / 16.f, 30.f / 16.f, 12.f / 16.f, 0.f, levelCollisionGroup);
            //...
            break;
        case TileName::PlatformSingleStart:
            m_pTiles[idx]->AddComponent<TextureTransformComponent>(64, 96, tileSize, tileSize);
            m_pTiles[idx]->AddComponent<BoxColliderComponent>(pRbyComp, 32.f / 16.f, 12.f / 16.f, 16.f / 16.f, 2.f / 16.f, 0.f, levelCollisionGroup);
            //...
            break;
        case TileName::PlatformSingleMiddle:
            m_pTiles[idx]->AddComponent<TextureTransformComponent>(96, 96, tileSize, tileSize);
            m_pTiles[idx]->AddComponent<BoxColliderComponent>(pRbyComp, 32.f / 16.f, 12.f / 16.f, 16.f / 16.f, 2.f / 16.f, 0.f, levelCollisionGroup);
            //...
            break;
        case TileName::PlatformSingleEnd:
            m_pTiles[idx]->AddComponent<TextureTransformComponent>(128, 96, tileSize, tileSize);
            m_pTiles[idx]->AddComponent<BoxColliderComponent>(pRbyComp, 32.f / 16.f, 12.f / 16.f, 16.f / 16.f, 2.f / 16.f, 0.f, levelCollisionGroup);
            //...
            break;
        case TileName::PlatformSingleStairStart:
            m_pTiles[idx]->AddComponent<TextureTransformComponent>(64, 64, tileSize, tileSize);
            m_pTiles[idx]->AddComponent<BoxColliderComponent>(pRbyComp, 4.f / 16.f, 12.f / 16.f, 03.f / 16.f, 2.f / 16.f, 0.f, levelCollisionGroup);
            m_pTiles[idx]->AddComponent<BoxColliderComponent>(pRbyComp, 4.f / 16.f, 12.f / 16.f, 30.f / 16.f, 2.f / 16.f, 0.f, levelCollisionGroup);
            //...
            break;
        case TileName::PlatformSingleStairMiddle:
            m_pTiles[idx]->AddComponent<TextureTransformComponent>(96, 64, tileSize, tileSize);
            m_pTiles[idx]->AddComponent<BoxColliderComponent>(pRbyComp, 4.f / 16.f, 12.f / 16.f, 03.f / 16.f, 2.f / 16.f, 0.f, levelCollisionGroup);
            m_pTiles[idx]->AddComponent<BoxColliderComponent>(pRbyComp, 4.f / 16.f, 12.f / 16.f, 30.f / 16.f, 2.f / 16.f, 0.f, levelCollisionGroup);
            //...
            break;
        case TileName::PlatformSingleStairEnd:
            m_pTiles[idx]->AddComponent<TextureTransformComponent>(128, 64, tileSize, tileSize);
            m_pTiles[idx]->AddComponent<BoxColliderComponent>(pRbyComp, 4.f / 16.f, 12.f / 16.f, 03.f / 16.f, 2.f / 16.f, 0.f, levelCollisionGroup);
            m_pTiles[idx]->AddComponent<BoxColliderComponent>(pRbyComp, 4.f / 16.f, 12.f / 16.f, 30.f / 16.f, 2.f / 16.f, 0.f, levelCollisionGroup);
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
        BurgerComponent* BrgComp = pIngredient->AddComponent<BurgerComponent>(pTfmComp, ingredient, ingredientSpriteSheet);

        if (GameObject* pGameObject = GetGameObject())
        {
            if (Scene* pScene = pGameObject->GetScene())
            {
                if (ScoreComponent* pScrComp = pScene->FindComponent<ScoreComponent>())
                {
                    BrgComp->AddObserver(pScrComp);
                }
            }
        }

        GetGameObject()->AddChild(pIngredient);
    }
}