#pragma once

struct SDL_Window;

class Stabulum
{
public:
	void Initialize();
	void LoadGame() const;
	void Cleanup();
	void Run();

//private:
protected:
	static const int MsPerFrame = 16; //7 for 144 fps, 16 for 60 fps, 33 for 30 fps => 1 / fps = msPerFrame
	SDL_Window* m_Window{};

	//void LoadTestScene() const;
	//void LoadLevel1() const;
};