#pragma once

struct SDL_Window;

class Stabulum
{
public:
	Stabulum() = default;
	virtual ~Stabulum() = default;

	Stabulum(const Stabulum& other) = delete;
	Stabulum(Stabulum&& other) noexcept = delete;
	Stabulum& operator=(const Stabulum& other) = delete;
	Stabulum& operator=(Stabulum&& other) noexcept = delete;

	void Initialize();
	void LoadGame() const;
	void Cleanup();
	void Run();

protected:
	static const int MsPerFrame = 16; //7 for 144 fps, 16 for 60 fps, 33 for 30 fps => 1 / fps = msPerFrame
	SDL_Window* m_Window{};
};