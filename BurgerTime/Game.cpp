#include "BurgerTimePCH.h"
#include "Game.h"

#include "InputManager.h"
#include "SceneManager.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include "GameObject.h"
#include "Scene.h"
#include "TimeManager.h"
#include "Structs.h"

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

//Observers
#include "Observer.h"

//Commands
#include "BaseCommand.h"
#include "LoseLifeCommand.h"
#include "QuitCommand.h"
#include "BurgerDroppedCommand.h"
#include "EnemyDiedCommand.h"
#include "MoveCommand.h"

void Game::Initialize()
{
	Stabulum::Initialize();

	ServiceLocator::RegisterSoundManager(new LoggingSoundManager{ new SDLSoundManager{} });
	ServiceLocator::GetSoundManager()->Init("../Resources/");
	ResourceManager::GetInstance().Init("../Resources/");
}

void Game::LoadGame() const
{
	//LoadTestScene();
	LoadLevel1();
}

void Game::Cleanup()
{
}

void Game::Run()
{
	Initialize();

	LoadGame();

	Stabulum::Run();

	ServiceLocator::RegisterSoundManager(nullptr);

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
	BurgerComponent* pBgrComp{};
	EnemyComponent* pEnmComp{};

	//Background
	auto spBackground = std::make_shared<GameObject>();

	pTfmComp = spBackground->AddComponent<TransformComponent>();
	pRdrComp = spBackground->AddComponent<RenderComponent>(pTfmComp, "background.jpg");

	scene.Add(spBackground);

	//Logo
	auto spLogo = std::make_shared<GameObject>();

	pTfmComp = spLogo->AddComponent<TransformComponent>(216.f, 180.f);
	pRdrComp = spLogo->AddComponent<RenderComponent>(pTfmComp, "logo.png");

	scene.Add(spLogo);

	//Title
	auto spFont = ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	auto spTitle = std::make_shared<GameObject>();

	pTfmComp = spTitle->AddComponent<TransformComponent>(80.f, 20.f);
	pRdrComp = spTitle->AddComponent<RenderComponent>(pTfmComp);
	pTxtComp = spTitle->AddComponent<TextComponent>(pRdrComp, spFont, RGBColor{ 255, 255, 255 }, "Programming 4 Assignment");

	scene.Add(spTitle);

	//Fps
	auto fps = std::make_shared<GameObject>();

	pTfmComp = fps->AddComponent<TransformComponent>(10.f, 10.f);
	pRdrComp = fps->AddComponent<RenderComponent>(pTfmComp);
	pTxtComp = fps->AddComponent<TextComponent>(pRdrComp, "Lingua.otf", 20, RGBColor{ 0, 150, 0 });
	pFpsComp = fps->AddComponent<FpsComponent>(pTxtComp);

	scene.Add(fps);

	//HealthDisplay 1
	auto spHealthDisplay1 = std::make_shared<GameObject>();
	pHltComp = spHealthDisplay1->AddComponent<HealthComponent>();
	pTfmComp = spHealthDisplay1->AddComponent<TransformComponent>(10.f, 100.f);
	pRdrComp = spHealthDisplay1->AddComponent<RenderComponent>(pTfmComp);
	pTxtComp = spHealthDisplay1->AddComponent<TextComponent>(pRdrComp, spFont, RGBColor{ 255, 150, 0 });

	scene.Add(spHealthDisplay1);

	//Scoreboard 1
	auto spScoreboard1 = std::make_shared<GameObject>();
	pScrComp = spScoreboard1->AddComponent<ScoreComponent>();
	pTfmComp = spScoreboard1->AddComponent<TransformComponent>(10.f, 200.f);
	pRdrComp = spScoreboard1->AddComponent<RenderComponent>(pTfmComp);
	pTxtComp = spScoreboard1->AddComponent<TextComponent>(pRdrComp, spFont, RGBColor{ 0, 150, 255 });

	scene.Add(spScoreboard1);

	//PeterPepper 1
	auto spPeterPepper1 = std::make_shared<GameObject>();
	pPtpComp = spPeterPepper1->AddComponent<PeterPepperComponent>();
	pPtpComp->AddObserver(pHltComp);

	scene.Add(spPeterPepper1);

	//Burger 1
	auto spBurger1 = std::make_shared<GameObject>();
	pBgrComp = spBurger1->AddComponent<BurgerComponent>();
	pBgrComp->AddObserver(pScrComp);

	scene.Add(spBurger1);

	//Enemy 1
	auto spEnemy1 = std::make_shared<GameObject>();
	pEnmComp = spEnemy1->AddComponent<EnemyComponent>();
	pEnmComp->AddObserver(pScrComp);

	scene.Add(spEnemy1);

	//HealthDisplay 2
	auto spHealthDisplay2 = std::make_shared<GameObject>();
	pHltComp = spHealthDisplay2->AddComponent<HealthComponent>();
	pTfmComp = spHealthDisplay2->AddComponent<TransformComponent>(100.f, 100.f);
	pRdrComp = spHealthDisplay2->AddComponent<RenderComponent>(pTfmComp);
	pTxtComp = spHealthDisplay2->AddComponent<TextComponent>(pRdrComp, spFont, RGBColor{ 255, 150, 0 });

	scene.Add(spHealthDisplay2);

	//Scoreboard 2
	auto spScoreboard2 = std::make_shared<GameObject>();
	pScrComp = spScoreboard2->AddComponent<ScoreComponent>();
	pTfmComp = spScoreboard2->AddComponent<TransformComponent>(100.f, 200.f);
	pRdrComp = spScoreboard2->AddComponent<RenderComponent>(pTfmComp);
	pTxtComp = spScoreboard2->AddComponent<TextComponent>(pRdrComp, spFont, RGBColor{ 0, 150, 255 });

	scene.Add(spScoreboard2);

	//PeterPepper 2
	auto spPeterPepper2 = std::make_shared<GameObject>();
	pPtpComp = spPeterPepper2->AddComponent<PeterPepperComponent>(10);
	pPtpComp->AddObserver(pHltComp);

	scene.Add(spPeterPepper2);

	//Burger 2
	auto spBurger2 = std::make_shared<GameObject>();
	pBgrComp = spBurger2->AddComponent<BurgerComponent>();
	pBgrComp->AddObserver(pScrComp);

	scene.Add(spBurger2);

	//Enemy 2
	auto spEnemy2 = std::make_shared<GameObject>();
	pEnmComp = spEnemy2->AddComponent<EnemyComponent>();
	pEnmComp->AddObserver(pScrComp);

	scene.Add(spEnemy2);

	//Input
	auto& inputManager = InputManager::GetInstance();

	inputManager.AddBindingToController(std::make_shared<LoseLifeCommand>(spPeterPepper1.get()), PS4Controller::Cross, InputState::Down, 0);
	inputManager.AddBindingToController(std::make_shared<BurgerDroppedCommand>(spBurger1.get()), PS4Controller::R1, InputState::Down, 0);
	inputManager.AddBindingToController(std::make_shared<EnemyDiedCommand>(spEnemy1.get()), PS4Controller::L1, InputState::Pressed, 0);

	//inputManager.AddBindingToKeyboard(std::make_shared<LoseLifeCommand>(spPeterPepper2.get()), ApplicationKeyboard::Space, InputState::Down);
	//inputManager.AddBindingToKeyboard(std::make_shared<BurgerDroppedCommand>(spBurger2.get()), ApplicationKeyboard::Q, InputState::Down);
	//inputManager.AddBindingToKeyboard(std::make_shared<EnemyDiedCommand>(spEnemy2.get()), ApplicationKeyboard::E, InputState::Pressed);

	inputManager.AddBindingToController(std::make_shared<LoseLifeCommand>(spPeterPepper2.get()), PS4Controller::Cross, InputState::Down, 1);
	inputManager.AddBindingToController(std::make_shared<BurgerDroppedCommand>(spBurger2.get()), PS4Controller::R1, InputState::Down, 1);
	inputManager.AddBindingToController(std::make_shared<EnemyDiedCommand>(spEnemy2.get()), PS4Controller::L1, InputState::Pressed, 1);

	inputManager.AddBindingToController<QuitCommand>(PS4Controller::Triangle, InputState::Up);
}

void Game::LoadLevel1() const
{
	/* Adjust window to level */
	//const FVec2 levelSize{ 416.f, 400.f };
	const glm::vec2 levelSize{ 416.f, 400.f };
	const float hudHeight{ 64.f }, border{ 16.f }, widthReal{ levelSize.x + border * 2.f }, heightReal{ levelSize.y + hudHeight };
	const float scale{ 1.5f }, widthScaled{ widthReal * scale }, heightScaled{ heightReal * scale };
	SDL_RenderSetScale(Renderer::GetInstance().GetSDLRenderer(), scale, scale);
	SDL_SetWindowSize(m_Window, static_cast<int>(widthScaled), static_cast<int>(heightScaled));

	//--- Scene ---//
	Scene& scene = SceneManager::GetInstance().CreateScene("Level1");

	std::cout << "\n===\nTo play a sound, press face button south. (To test this sound, it is bound to losing a life.)\n===\n" << std::endl;

	//--- Components ---//
	TextureTransformComponent* pTtmComp{};
	TransformComponent* pTfmComp{};
	RenderComponent* pRdrComp{};
	TextComponent* pTxtComp{};
	SpriteComponent* pSprComp{};
	MovementComponent* pMvmComp{};

	//### World
	auto spWorld = std::make_shared<GameObject>();

	spWorld->AddComponent<WorldComponent>();

	scene.Add(spWorld);

	//### Background
	auto spBackground = std::make_shared<GameObject>();

	pTfmComp = spBackground->AddComponent<TransformComponent>(border, hudHeight);
	pRdrComp = spBackground->AddComponent<RenderComponent>(pTfmComp, "Textures/Levels/Level1/Background.png");

	scene.Add(spBackground);

	//### High score
	auto spFont16 = ResourceManager::GetInstance().LoadFont("Fonts/PressStartK-EX89.otf", 16);
	RGBColor red{ 255, 0, 0 };
	RGBColor beige{ 255, 255, 222 };

	//Text
	auto spHighScoreText = std::make_shared<GameObject>();

	pTfmComp = spHighScoreText->AddComponent<TransformComponent>(border + 96.f, 8.f);
	pRdrComp = spHighScoreText->AddComponent<RenderComponent>(pTfmComp);
	pTxtComp = spHighScoreText->AddComponent<TextComponent>(pRdrComp, spFont16, red, "HI_SCORE");

	scene.Add(spHighScoreText);

	//score
	auto spHighScore = std::make_shared<GameObject>();

	pTfmComp = spHighScore->AddComponent<TransformComponent>(border + 208.f, 28.f);
	pRdrComp = spHighScore->AddComponent<RenderComponent>(pTfmComp);
	pRdrComp->SetAllignment(Renderer::Allign::TopRight);
	pTxtComp = spHighScore->AddComponent<TextComponent>(pRdrComp, spFont16, beige, "28000");

	scene.Add(spHighScore);

	//### Score
	//Text
	auto spScoreText = std::make_shared<GameObject>();

	pTfmComp = spScoreText->AddComponent<TransformComponent>(border + 16.f, 8.f);
	pRdrComp = spScoreText->AddComponent<RenderComponent>(pTfmComp);
	pTxtComp = spScoreText->AddComponent<TextComponent>(pRdrComp, spFont16, red, "1UP");

	scene.Add(spScoreText);

	//score
	auto spScore = std::make_shared<GameObject>();

	pTfmComp = spScore->AddComponent<TransformComponent>(border + 80.f, 28.f);
	pRdrComp = spScore->AddComponent<RenderComponent>(pTfmComp);
	pRdrComp->SetAllignment(Renderer::Allign::TopRight);
	pTxtComp = spScore->AddComponent<TextComponent>(pRdrComp, spFont16, beige, "200");

	scene.Add(spScore);

	//### Pepper
	//Texture
	auto spPepperTexture = std::make_shared<GameObject>();

	pTtmComp = spPepperTexture->AddComponent<TextureTransformComponent>(32, 16, 48, 16);
	pTfmComp = spPepperTexture->AddComponent<TransformComponent>(widthReal, 8.f);
	pRdrComp = spPepperTexture->AddComponent<RenderComponent>(pTfmComp, "Textures/Icons/Icons.png");
	pRdrComp->SetAllignment(Renderer::Allign::TopRight);

	scene.Add(spPepperTexture);

	//Number
	auto spPeppers = std::make_shared<GameObject>();

	pTfmComp = spPeppers->AddComponent<TransformComponent>(widthReal, 28.f);
	pRdrComp = spPeppers->AddComponent<RenderComponent>(pTfmComp);
	pRdrComp->SetAllignment(Renderer::Allign::TopRight);
	pTxtComp = spPeppers->AddComponent<TextComponent>(pRdrComp, spFont16, beige, "5");

	scene.Add(spPeppers);

	//### Peter Pepper Sprite
	auto spPeterPepperSprite = std::make_shared<GameObject>();

	pTfmComp = spPeterPepperSprite->AddComponent<TransformComponent>(widthReal / 2.f - 16.f, heightReal - 120.f);
	pRdrComp = spPeterPepperSprite->AddComponent<RenderComponent>(pTfmComp, "Textures/Characters/PeterPepper/Move.png");
	pTtmComp = spPeterPepperSprite->AddComponent<TextureTransformComponent>(0, 0, 0, 0);
	pSprComp = spPeterPepperSprite->AddComponent<SpriteComponent>(pRdrComp, pTtmComp, 4, 3);
	auto pTest = spPeterPepperSprite->AddComponent<RigidBodyComponent>(pTfmComp, RigidBodyComponent::BodyType::Dynamic);
	pMvmComp = spPeterPepperSprite->AddComponent<MovementComponent>(pSprComp, pTest);

	spPeterPepperSprite->SetParent(spWorld.get());

	scene.Add(spPeterPepperSprite);

	//### Sound Test
	auto spSoundTest = std::make_shared<GameObject>();

	spSoundTest->AddComponent<PeterPepperComponent>();

	scene.Add(spSoundTest);

	//--- Input ---//
	auto& inputManager = InputManager::GetInstance();

	inputManager.AddBindingToController(std::make_shared<MoveUpCommand>(spPeterPepperSprite.get()), PS4Controller::DPadUp, InputState::Pressed);
	inputManager.AddBindingToController(std::make_shared<MoveDownCommand>(spPeterPepperSprite.get()), PS4Controller::DPadDown, InputState::Pressed);
	inputManager.AddBindingToController(std::make_shared<MoveLeftCommand>(spPeterPepperSprite.get()), PS4Controller::DPadLeft, InputState::Pressed);
	inputManager.AddBindingToController(std::make_shared<MoveRightCommand>(spPeterPepperSprite.get()), PS4Controller::DPadRight, InputState::Pressed);

	inputManager.AddBindingToKeyboard(std::make_shared<MoveUpCommand>(spPeterPepperSprite.get()), ApplicationKeyboard::ArrowUp, InputState::Pressed);
	inputManager.AddBindingToKeyboard(std::make_shared<MoveDownCommand>(spPeterPepperSprite.get()), ApplicationKeyboard::ArrowDown, InputState::Pressed);
	inputManager.AddBindingToKeyboard(std::make_shared<MoveLeftCommand>(spPeterPepperSprite.get()), ApplicationKeyboard::ArrowLeft, InputState::Pressed);
	inputManager.AddBindingToKeyboard(std::make_shared<MoveRightCommand>(spPeterPepperSprite.get()), ApplicationKeyboard::ArrowRight, InputState::Pressed);

	inputManager.AddBindingToController(std::make_shared<LoseLifeCommand>(spSoundTest.get()), PS4Controller::Cross, InputState::Down);

	inputManager.AddBindingToKeyboard(std::make_shared<LoseLifeCommand>(spSoundTest.get()), ApplicationKeyboard::Space, InputState::Down);

	inputManager.AddBindingToController<QuitCommand>(PS4Controller::Triangle, InputState::Up);
	
	inputManager.AddBindingToKeyboard<QuitCommand>(ApplicationKeyboard::Escape, InputState::Up);
}