#include "BurgerTimePCH.h"
#include "Game.h"

#include <fstream>

#include "InputManager.h"
#include "SceneManager.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include "Scene.h"
#include "TimeManager.h"
#include "Structs.h"
#include "RenderOrder.h"

//Services
#include "ServiceLocator.h"

//Components
#include "BaseComponent.h"
#include "TransformComponent.h"
#include "TextureTransformComponent.h"
#include "RenderComponent.h"
#include "TextComponent.h"
#include "FpsComponent.h"
#include "HealthComponent.h"
#include "ScoreComponent.h"
#include "BurgerComponent.h"
#include "EnemyComponent.h"
#include "PeterPepperComponent.h"
#include "SpriteComponent.h"
#include "MovementComponent.h"
#include "WorldComponent.h"
#include "RigidBodyComponent.h"
#include "BoxColliderComponent.h"
#include "CircleColliderComponent.h"
#include "LevelComponent.h"

//Observers
#include "Observer.h"

//Commands
#include "BaseCommand.h"
#include "LoseLifeCommand.h"
#include "QuitCommand.h"
#include "BurgerDroppedCommand.h"
#include "EnemyDiedCommand.h"
#include "MoveCommand.h"
#include "SceneBackwardCommand.h"
#include "SceneForwardCommand.h"

void Game::Initialize()
{
	Stabulum::Initialize();

	//Normal or logging sound manager
	ServiceLocator::RegisterSoundManager(new SDLSoundManager{});

	//Initialize data location
	ServiceLocator::GetSoundManager()->Init("../Resources/");
	ResourceManager::GetInstance().Init("../Resources/");
}

void Game::LoadGame()
{
	//Render
	Renderer& renderer = Renderer::GetInstance();

	/* Adjust window to level */
	const float hudHeight{ 64.f }, widthReal{ m_LevelSize.x + m_Border * 2.f }, heightReal{ m_LevelSize.y + hudHeight };
	const float scaleX{ 1.5f }, scaleY{ 2.f }, widthScaled{ widthReal * scaleX }, heightScaled{ heightReal * scaleY };
	SDL_RenderSetScale(renderer.GetSDLRenderer(), scaleX, scaleY);
	SDL_SetWindowSize(m_Window, static_cast<int>(widthScaled), static_cast<int>(heightScaled));
	SDL_SetWindowPosition(m_Window, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);

	//Layers
	for (int idx{}; idx < static_cast<int>(RenderOrder::Amount); ++idx)
	{
		renderer.AddLayer();
	}

	//Load sound
	ServiceLocator::GetSoundManager()->Load("Sounds/GameMusic.mp3", 10);
	ServiceLocator::GetSoundManager()->Load("Sounds/IngredientWalk.mp3", 1);
	ServiceLocator::GetSoundManager()->Load("Sounds/Thud.mp3", 2);

	//Load highscore
	std::string filePath{ "../Resources/Score/HighScore.txt" };
	std::ifstream inputFile(filePath);

	int highScore{};

	if (inputFile.is_open())
	{
		inputFile >> highScore;
		inputFile.close();
	}

	//LoadTestScene();
	LoadLevel("../Resources/Level/Level1.txt", 1, highScore);
	LoadLevel("../Resources/Level/Level2.txt", 2, highScore);
	LoadLevel("../Resources/Level/Level3.txt", 3, highScore);
	LoadLevel("../Resources/Level/Level4.txt", 4, highScore);
	LoadLevel("../Resources/Level/Level5.txt", 5, highScore);
	LoadLevel("../Resources/Level/Level6.txt", 6, highScore);

	//--- General Input ---//
	auto& inputManager = InputManager::GetInstance();

	inputManager.AddBindingToController<QuitCommand>(PS4Controller::Triangle, InputState::Up);
	inputManager.AddBindingToKeyboard<QuitCommand>(ApplicationKeyboard::Escape, InputState::Up);

	inputManager.AddBindingToController<SceneBackwardCommand>(PS4Controller::R1, InputState::Up);
	inputManager.AddBindingToController<SceneForwardCommand>(PS4Controller::L1, InputState::Up);
	inputManager.AddBindingToKeyboard<SceneBackwardCommand>(ApplicationKeyboard::F4, InputState::Up);
	inputManager.AddBindingToKeyboard<SceneForwardCommand>(ApplicationKeyboard::F3, InputState::Up);
}

void Game::Cleanup()
{
	//Save (high)score
	HighScore();

	//Destroy sound manager
	ServiceLocator::RegisterSoundManager(nullptr);

	//Delete gameobjects
	for (GameObject* pLevel : m_pLevels)
	{
		if (pLevel)
		{
			delete pLevel;
			pLevel = nullptr;
		}
	}

	for (GameObject* pPeterPepper : m_pPeterPeppers)
	{
		if (pPeterPepper)
		{
			delete pPeterPepper;
			pPeterPepper = nullptr;
		}
	}
}

void Game::Run()
{
	Initialize();

	LoadGame();

	Stabulum::Run();

	Cleanup();
}

void Game::LoadLevel(const std::string& levelFile, const int levelIndex, int highScore)
{
	/* Adjust window to level */
	const float widthReal{ m_LevelSize.x + m_Border * 2.f };

	//--- Scene ---//
	Scene& scene = SceneManager::GetInstance().CreateScene("BurgerTimeLevel" + std::to_string(levelIndex));

	//--- Components ---//
	TextureTransformComponent*	pTtmComp{};
	TransformComponent*			pTfmComp{};
	RenderComponent*			pRdrComp{};
	TextComponent*				pTxtComp{};
	SpriteComponent*			pSprComp{};
	MovementComponent*			pMvmComp{};
	RigidBodyComponent*			pRbyComp{};
	LevelComponent*				pLvlComp{};
	CircleColliderComponent*	pCcdComp{};

	//### World
	auto spWorld = std::make_shared<GameObject>();

	spWorld->AddComponent<WorldComponent>();

	scene.Add(spWorld);

	//### Level
	GameObject* pLevel{ new GameObject{} };
	pLevel->AddComponent<TransformComponent>(-8.f, 32.f);
	pLvlComp = pLevel->AddComponent<LevelComponent>(levelFile);

	m_pLevels.emplace_back(pLevel);

	pLevel->SetParent(spWorld.get());

	//### High score
	auto spFont16 = ResourceManager::GetInstance().LoadFont("Fonts/PressStartK-EX89.otf", 16);
	RGBColor red{ 255, 0, 0 };
	RGBColor beige{ 255, 255, 222 };

	//Text
	auto spHighScoreText = std::make_shared<GameObject>();

	pTfmComp = spHighScoreText->AddComponent<TransformComponent>(m_Border + 96.f, 8.f);
	pRdrComp = spHighScoreText->AddComponent<RenderComponent>(pTfmComp, static_cast<int>(RenderOrder::UI));
	pTxtComp = spHighScoreText->AddComponent<TextComponent>(pRdrComp, spFont16, red, "HI_SCORE");

	scene.Add(spHighScoreText);

	//score
	auto spHighScore = std::make_shared<GameObject>();

	pTfmComp = spHighScore->AddComponent<TransformComponent>(m_Border + 208.f, 28.f);
	pRdrComp = spHighScore->AddComponent<RenderComponent>(pTfmComp, static_cast<int>(RenderOrder::UI));
	pRdrComp->SetAllignment(Renderer::Allign::TopRight);
	pTxtComp = spHighScore->AddComponent<TextComponent>(pRdrComp, spFont16, beige, std::to_string(highScore));

	scene.Add(spHighScore);

	//### Score
	//Text
	auto spScoreText = std::make_shared<GameObject>();

	pTfmComp = spScoreText->AddComponent<TransformComponent>(m_Border + 16.f, 8.f);
	pRdrComp = spScoreText->AddComponent<RenderComponent>(pTfmComp, static_cast<int>(RenderOrder::UI));
	pTxtComp = spScoreText->AddComponent<TextComponent>(pRdrComp, spFont16, red, "1UP");

	scene.Add(spScoreText);

	//score
	auto spScore = std::make_shared<GameObject>();

	spScore->AddComponent<ScoreComponent>();
	pTfmComp = spScore->AddComponent<TransformComponent>(m_Border + 80.f, 28.f);
	pRdrComp = spScore->AddComponent<RenderComponent>(pTfmComp, static_cast<int>(RenderOrder::UI));
	pRdrComp->SetAllignment(Renderer::Allign::TopRight);
	pTxtComp = spScore->AddComponent<TextComponent>(pRdrComp, spFont16, beige, "0");

	scene.Add(spScore);

	//### Pepper
	//Texture
	auto spPepperTexture = std::make_shared<GameObject>();

	pTtmComp = spPepperTexture->AddComponent<TextureTransformComponent>(32, 16, 48, 16);
	pTfmComp = spPepperTexture->AddComponent<TransformComponent>(widthReal, 8.f);
	pRdrComp = spPepperTexture->AddComponent<RenderComponent>(pTfmComp, static_cast<int>(RenderOrder::UI), "Textures/BurgerTime/Icons/Icons.png");
	pRdrComp->SetAllignment(Renderer::Allign::TopRight);

	scene.Add(spPepperTexture);

	//Number
	auto spPeppers = std::make_shared<GameObject>();

	pTfmComp = spPeppers->AddComponent<TransformComponent>(widthReal, 28.f);
	pRdrComp = spPeppers->AddComponent<RenderComponent>(pTfmComp, static_cast<int>(RenderOrder::UI));
	pRdrComp->SetAllignment(Renderer::Allign::TopRight);
	pTxtComp = spPeppers->AddComponent<TextComponent>(pRdrComp, spFont16, beige, "5");

	scene.Add(spPeppers);

	//### Peter Pepper Sprite
	GameObject* pPeterPepper{ new GameObject{} };

	pTfmComp = pPeterPepper->AddComponent<TransformComponent>(pLvlComp->GetPlayerPosition() + pLevel->GetComponent<TransformComponent>()->GetWorldPosition());
	pRdrComp = pPeterPepper->AddComponent<RenderComponent>(pTfmComp, static_cast<int>(RenderOrder::Player), "Textures/BurgerTime/Characters/PeterPepper/Move.png");
	pTtmComp = pPeterPepper->AddComponent<TextureTransformComponent>(0, 0, 0, 0);
	pSprComp = pPeterPepper->AddComponent<SpriteComponent>(pRdrComp, pTtmComp, 4, 3);
	pRbyComp = pPeterPepper->AddComponent<RigidBodyComponent>(pTfmComp, RigidBodyComponent::BodyType::Dynamic);
	pCcdComp = pPeterPepper->AddComponent<CircleColliderComponent>(pRbyComp, 0.6f, FVec2{ 1.f, 1.5f }, static_cast<int>(ColliderComponent::CollisionGroup::Level));
	pMvmComp = pPeterPepper->AddComponent<MovementComponent>(pSprComp, pRbyComp);
	m_pPeterPeppers.emplace_back(pPeterPepper);

	pPeterPepper->SetParent(spWorld.get());

	//### Peter Pepper Sprite 2
	GameObject* pPeterPepper2{ new GameObject{} };

	pTfmComp = pPeterPepper2->AddComponent<TransformComponent>(pLvlComp->GetPlayerPosition() + pLevel->GetComponent<TransformComponent>()->GetWorldPosition());
	pRdrComp = pPeterPepper2->AddComponent<RenderComponent>(pTfmComp, static_cast<int>(RenderOrder::Player), "Textures/BurgerTime/Characters/PeterPepper/Move.png");
	pTtmComp = pPeterPepper2->AddComponent<TextureTransformComponent>(0, 0, 0, 0);
	pSprComp = pPeterPepper2->AddComponent<SpriteComponent>(pRdrComp, pTtmComp, 4, 3);
	pRbyComp = pPeterPepper2->AddComponent<RigidBodyComponent>(pTfmComp, RigidBodyComponent::BodyType::Dynamic);
	pCcdComp = pPeterPepper2->AddComponent<CircleColliderComponent>(pRbyComp, 0.6f, FVec2{ 1.f, 1.5f }, static_cast<int>(ColliderComponent::CollisionGroup::Level));
	pMvmComp = pPeterPepper2->AddComponent<MovementComponent>(pSprComp, pRbyComp);
	m_pPeterPeppers.emplace_back(pPeterPepper2);

	pPeterPepper2->SetParent(spWorld.get());

	//--- Input ---//
	auto& inputManager = InputManager::GetInstance();

	inputManager.AddBindingToController(std::make_shared<MoveUpCommand>(pPeterPepper), PS4Controller::DPadUp, InputState::Pressed);
	inputManager.AddBindingToController(std::make_shared<MoveDownCommand>(pPeterPepper), PS4Controller::DPadDown, InputState::Pressed);
	inputManager.AddBindingToController(std::make_shared<MoveLeftCommand>(pPeterPepper), PS4Controller::DPadLeft, InputState::Pressed);
	inputManager.AddBindingToController(std::make_shared<MoveRightCommand>(pPeterPepper), PS4Controller::DPadRight, InputState::Pressed);

	inputManager.AddBindingToKeyboard(std::make_shared<MoveUpCommand>(pPeterPepper2), ApplicationKeyboard::ArrowUp, InputState::Pressed);
	inputManager.AddBindingToKeyboard(std::make_shared<MoveDownCommand>(pPeterPepper2), ApplicationKeyboard::ArrowDown, InputState::Pressed);
	inputManager.AddBindingToKeyboard(std::make_shared<MoveLeftCommand>(pPeterPepper2), ApplicationKeyboard::ArrowLeft, InputState::Pressed);
	inputManager.AddBindingToKeyboard(std::make_shared<MoveRightCommand>(pPeterPepper2), ApplicationKeyboard::ArrowRight, InputState::Pressed);
}

void Game::HighScore()
{
	int score = SceneManager::GetInstance().GetActiveScene()->FindComponent<ScoreComponent>()->GetScore();

	std::string filePath{ "../Resources/Score/HighScore.txt" };
	std::ifstream inputFile(filePath);

	if (!inputFile.is_open())
	{
		//write new file
		std::ofstream outputFile{ filePath };

		if (outputFile.is_open())
		{
			outputFile.write(std::to_string(score).c_str(), sizeof(const char*));
			outputFile.close();
		}
	}
	else
	{
		//compare old file
		int oldScore;
		inputFile >> oldScore;
		inputFile.close();

		if (score > oldScore)
		{
			//overwrite file
			std::ofstream outputFile{ filePath };

			if (outputFile.is_open())
			{
				outputFile.write(std::to_string(score).c_str(), sizeof(const char*));
				outputFile.close();
			}
		}
	}
}