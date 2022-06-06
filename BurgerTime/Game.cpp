#include "BurgerTimePCH.h"
#include "Game.h"

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
#include "NextSceneCommand.h"
#include "PreviousSceneCommand.h"

void Game::Initialize()
{
	Stabulum::Initialize();

	ServiceLocator::RegisterSoundManager(new LoggingSoundManager{ new SDLSoundManager{} });
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

	//LoadTestScene();
	LoadLevel("../Resources/Level/Level1.txt", 1);
	LoadLevel("../Resources/Level/Level2.txt", 2);
	LoadLevel("../Resources/Level/Level3.txt", 3);
	LoadLevel("../Resources/Level/Level4.txt", 4);
	LoadLevel("../Resources/Level/Level5.txt", 5);
	LoadLevel("../Resources/Level/Level6.txt", 6);

	////--- General Input ---//
	auto& inputManager = InputManager::GetInstance();

	inputManager.AddBindingToController<QuitCommand>(PS4Controller::Triangle, InputState::Up);
	inputManager.AddBindingToKeyboard<QuitCommand>(ApplicationKeyboard::Escape, InputState::Up);

	inputManager.AddBindingToController<NextSceneCommand>(PS4Controller::R1, InputState::Up);
	inputManager.AddBindingToController<PreviousSceneCommand>(PS4Controller::L1, InputState::Up);
	inputManager.AddBindingToKeyboard<NextSceneCommand>(ApplicationKeyboard::F4, InputState::Up);
	inputManager.AddBindingToKeyboard<PreviousSceneCommand>(ApplicationKeyboard::F3, InputState::Up);
}

void Game::Cleanup()
{
	ServiceLocator::RegisterSoundManager(nullptr);

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

void Game::LoadTestScene() const
{
	//Scene
	Scene& scene = SceneManager::GetInstance().CreateScene("FPS");

	//Components
	TransformComponent* pTfmComp{};
	RenderComponent* pRdrComp{};
	TextComponent* pTxtComp{};
	FpsComponent* pFpsComp{};
	HealthComponent* pHltComp{};
	ScoreComponent* pScrComp{};
	PeterPepperComponent* pPtpComp{};
	//BurgerComponent* pBgrComp{};
	EnemyComponent* pEnmComp{};

	//Background
	auto spBackground = std::make_shared<GameObject>();

	pTfmComp = spBackground->AddComponent<TransformComponent>();
	pRdrComp = spBackground->AddComponent<RenderComponent>(pTfmComp, static_cast<int>(RenderOrder::Level), "Textures/Minigin/background.jpg");

	scene.Add(spBackground);

	//Logo
	auto spLogo = std::make_shared<GameObject>();

	pTfmComp = spLogo->AddComponent<TransformComponent>(216.f, 180.f);
	pRdrComp = spLogo->AddComponent<RenderComponent>(pTfmComp, static_cast<int>(RenderOrder::UI), "Textures/Minigin/logo.png");

	scene.Add(spLogo);

	//Title
	auto spFont = ResourceManager::GetInstance().LoadFont("Fonts/Lingua.otf", 36);
	auto spTitle = std::make_shared<GameObject>();

	pTfmComp = spTitle->AddComponent<TransformComponent>(80.f, 20.f);
	pRdrComp = spTitle->AddComponent<RenderComponent>(pTfmComp, static_cast<int>(RenderOrder::UI));
	pTxtComp = spTitle->AddComponent<TextComponent>(pRdrComp, spFont, RGBColor{ 255, 255, 255 }, "Programming 4 Assignment");

	scene.Add(spTitle);

	//Fps
	auto fps = std::make_shared<GameObject>();

	pTfmComp = fps->AddComponent<TransformComponent>(10.f, 10.f);
	pRdrComp = fps->AddComponent<RenderComponent>(pTfmComp, static_cast<int>(RenderOrder::UI));
	pTxtComp = fps->AddComponent<TextComponent>(pRdrComp, "Fonts/Lingua.otf", 20, RGBColor{ 0, 150, 0 });
	pFpsComp = fps->AddComponent<FpsComponent>(pTxtComp);

	scene.Add(fps);

	//HealthDisplay 1
	auto spHealthDisplay1 = std::make_shared<GameObject>();
	pHltComp = spHealthDisplay1->AddComponent<HealthComponent>();
	pTfmComp = spHealthDisplay1->AddComponent<TransformComponent>(10.f, 100.f);
	pRdrComp = spHealthDisplay1->AddComponent<RenderComponent>(pTfmComp, static_cast<int>(RenderOrder::HUD));
	pTxtComp = spHealthDisplay1->AddComponent<TextComponent>(pRdrComp, spFont, RGBColor{ 255, 150, 0 });

	scene.Add(spHealthDisplay1);

	//Scoreboard 1
	auto spScoreboard1 = std::make_shared<GameObject>();
	pScrComp = spScoreboard1->AddComponent<ScoreComponent>();
	pTfmComp = spScoreboard1->AddComponent<TransformComponent>(10.f, 200.f);
	pRdrComp = spScoreboard1->AddComponent<RenderComponent>(pTfmComp, static_cast<int>(RenderOrder::HUD));
	pTxtComp = spScoreboard1->AddComponent<TextComponent>(pRdrComp, spFont, RGBColor{ 0, 150, 255 });

	scene.Add(spScoreboard1);

	//PeterPepper 1
	auto spPeterPepper1 = std::make_shared<GameObject>();
	pPtpComp = spPeterPepper1->AddComponent<PeterPepperComponent>();
	pPtpComp->AddObserver(pHltComp);

	scene.Add(spPeterPepper1);

	////Burger 1
	//auto spBurger1 = std::make_shared<GameObject>();
	//pBgrComp = spBurger1->AddComponent<BurgerComponent>();
	//pBgrComp->AddObserver(pScrComp);

	//scene.Add(spBurger1);

	//Enemy 1
	auto spEnemy1 = std::make_shared<GameObject>();
	pEnmComp = spEnemy1->AddComponent<EnemyComponent>();
	pEnmComp->AddObserver(pScrComp);

	scene.Add(spEnemy1);

	//HealthDisplay 2
	auto spHealthDisplay2 = std::make_shared<GameObject>();
	pHltComp = spHealthDisplay2->AddComponent<HealthComponent>();
	pTfmComp = spHealthDisplay2->AddComponent<TransformComponent>(100.f, 100.f);
	pRdrComp = spHealthDisplay2->AddComponent<RenderComponent>(pTfmComp, static_cast<int>(RenderOrder::HUD));
	pTxtComp = spHealthDisplay2->AddComponent<TextComponent>(pRdrComp, spFont, RGBColor{ 255, 150, 0 });

	scene.Add(spHealthDisplay2);

	//Scoreboard 2
	auto spScoreboard2 = std::make_shared<GameObject>();
	pScrComp = spScoreboard2->AddComponent<ScoreComponent>();
	pTfmComp = spScoreboard2->AddComponent<TransformComponent>(100.f, 200.f);
	pRdrComp = spScoreboard2->AddComponent<RenderComponent>(pTfmComp, static_cast<int>(RenderOrder::HUD));
	pTxtComp = spScoreboard2->AddComponent<TextComponent>(pRdrComp, spFont, RGBColor{ 0, 150, 255 });

	scene.Add(spScoreboard2);

	//PeterPepper 2
	auto spPeterPepper2 = std::make_shared<GameObject>();
	pPtpComp = spPeterPepper2->AddComponent<PeterPepperComponent>(10);
	pPtpComp->AddObserver(pHltComp);

	scene.Add(spPeterPepper2);

	////Burger 2
	//auto spBurger2 = std::make_shared<GameObject>();
	//pBgrComp = spBurger2->AddComponent<BurgerComponent>();
	//pBgrComp->AddObserver(pScrComp);

	//scene.Add(spBurger2);

	//Enemy 2
	auto spEnemy2 = std::make_shared<GameObject>();
	pEnmComp = spEnemy2->AddComponent<EnemyComponent>();
	pEnmComp->AddObserver(pScrComp);

	scene.Add(spEnemy2);

	//Input
	auto& inputManager = InputManager::GetInstance();

	inputManager.AddBindingToController(std::make_shared<LoseLifeCommand>(spPeterPepper1.get()), PS4Controller::Cross, InputState::Down, 0);
	//inputManager.AddBindingToController(std::make_shared<BurgerDroppedCommand>(spBurger1.get()), PS4Controller::R1, InputState::Down, 0);
	inputManager.AddBindingToController(std::make_shared<EnemyDiedCommand>(spEnemy1.get()), PS4Controller::L1, InputState::Pressed, 0);

	inputManager.AddBindingToKeyboard(std::make_shared<LoseLifeCommand>(spPeterPepper2.get()), ApplicationKeyboard::Space, InputState::Down);
	//inputManager.AddBindingToKeyboard(std::make_shared<BurgerDroppedCommand>(spBurger2.get()), ApplicationKeyboard::Q, InputState::Down);
	inputManager.AddBindingToKeyboard(std::make_shared<EnemyDiedCommand>(spEnemy2.get()), ApplicationKeyboard::E, InputState::Pressed);

	inputManager.AddBindingToController(std::make_shared<LoseLifeCommand>(spPeterPepper2.get()), PS4Controller::Cross, InputState::Down, 1);
	//inputManager.AddBindingToController(std::make_shared<BurgerDroppedCommand>(spBurger2.get()), PS4Controller::R1, InputState::Down, 1);
	inputManager.AddBindingToController(std::make_shared<EnemyDiedCommand>(spEnemy2.get()), PS4Controller::L1, InputState::Pressed, 1);

	inputManager.AddBindingToController<QuitCommand>(PS4Controller::Triangle, InputState::Up);
}

void Game::LoadLevel(const std::string& levelFile, const int levelIndex)
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
	pTxtComp = spHighScore->AddComponent<TextComponent>(pRdrComp, spFont16, beige, "28000");

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

	//inputManager.AddBindingToController<QuitCommand>(PS4Controller::Triangle, InputState::Up);
	//inputManager.AddBindingToKeyboard<QuitCommand>(ApplicationKeyboard::Escape, InputState::Up);

	//inputManager.AddBindingToKeyboard<NextSceneCommand>(ApplicationKeyboard::F4, InputState::Up);
	//inputManager.AddBindingToKeyboard<PreviousSceneCommand>(ApplicationKeyboard::F3, InputState::Up);
}