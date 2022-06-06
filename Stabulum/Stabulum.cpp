#include "StabulumPCH.h"
#include "Stabulum.h"

#include <thread>

#include "InputManager.h"
#include "SceneManager.h"
#include "TimeManager.h"
#include "Renderer.h"

using namespace std;

void PrintSDLVersion()
{
	SDL_version compiled{};
	SDL_version linked{};

	SDL_VERSION(&compiled);
	SDL_GetVersion(&linked);
	printf("We compiled against SDL version %d.%d.%d ...\n",
		compiled.major, compiled.minor, compiled.patch);
	printf("We are linking against SDL version %d.%d.%d.\n",
		linked.major, linked.minor, linked.patch);
}

void Stabulum::Initialize()
{
	PrintSDLVersion();
	
	if (SDL_Init(SDL_INIT_VIDEO & SDL_INIT_AUDIO) != 0) 
	{
		throw std::runtime_error(std::string("SDL_Init Error: ") + SDL_GetError());
	}

	m_Window = SDL_CreateWindow(
		"Stabulum: Programming 4 Engine",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		640,
		480,
		SDL_WINDOW_OPENGL
	);

	if (m_Window == nullptr) 
	{
		throw std::runtime_error(std::string("SDL_CreateWindow Error: ") + SDL_GetError());
	}

	Renderer::GetInstance().Init(m_Window);
}

void Stabulum::LoadGame() const
{
	//...
}

void Stabulum::Cleanup()
{
	Renderer::GetInstance().Destroy();
	SDL_DestroyWindow(m_Window);
	m_Window = nullptr;
	SDL_Quit();
}

void Stabulum::Run()
{
	{
		auto& renderer = Renderer::GetInstance();
		auto& sceneManager = SceneManager::GetInstance();
		auto& input = InputManager::GetInstance();

		bool doContinue{ true };
		auto lastTime{ chrono::high_resolution_clock::now() };
		float lag{};

		while (doContinue)
		{
			const auto currentTime{ chrono::high_resolution_clock::now() };
			float deltaTime{ chrono::duration<float>(currentTime - lastTime).count() };

			lastTime = currentTime;
			lag += deltaTime;

			doContinue = input.ProcessInput();
			input.HandleInput();

			while (lag >= TimeManager::FixedTimeStep)
			{
				//Fixed update (for physics and networking)
				sceneManager.FixedUpdate(TimeManager::FixedTimeStep);
				lag -= TimeManager::FixedTimeStep;
			}

			TimeManager::DeltaTime = deltaTime;
			sceneManager.Update();
			renderer.Render();

			auto sleepTime{ chrono::duration_cast<chrono::duration<float>>(currentTime + chrono::milliseconds(MsPerFrame) - chrono::high_resolution_clock::now()) };
			if (sleepTime.count() > 0.f)
			{
				this_thread::sleep_for(sleepTime);
			}
		}
	}

	Cleanup();
}