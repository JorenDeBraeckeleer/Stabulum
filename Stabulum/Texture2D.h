#pragma once

struct SDL_Texture;

//Simple RAII wrapper for an SDL_Texture

class Texture2D final
{
public:
	explicit Texture2D(SDL_Texture* texture);
	~Texture2D();

	Texture2D(const Texture2D &) = delete;
	Texture2D(Texture2D &&) = delete;
	Texture2D & operator= (const Texture2D &) = delete;
	Texture2D & operator= (const Texture2D &&) = delete;

	SDL_Texture* GetSDLTexture() const;

private:
	SDL_Texture* m_Texture;
};