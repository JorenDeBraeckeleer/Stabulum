#pragma once
#include "Singleton.h"

class Texture2D;

//Simple RAII wrapper for the SDL renderer

class Renderer final : public Singleton<Renderer>
{
public:
	void Init(SDL_Window* window);
	void Render() const;
	void Destroy();

	enum class Allign
	{
		TopLeft = 0,
		BottomLeft = 1,
		BottomRight = 2,
		TopRight = 3,
	};

	void RenderTexture(const Texture2D& texture, float x, float y, const Allign& allignment = Allign::TopLeft) const;
	void RenderTexture(const Texture2D& texture, float x, float y, float width, float height, const Allign& allignment = Allign::TopLeft) const;
	void RenderTexture(const Texture2D& texture, float srcX, float srcY, float srcWidth, float srcHeight, float dstX, float dstY, const Allign& allignment = Allign::TopLeft) const;
	void RenderTexture(const Texture2D& texture, SDL_Rect* pSrcRect, float dstX, float dstY, const Allign& allignment = Allign::TopLeft) const;

	void AllignmentCheck(const Texture2D& texture, int& dstX, int& dstY, const Allign& allignment, SDL_Rect* pSrcRect = nullptr) const;

	SDL_Renderer* GetSDLRenderer() const { return m_Renderer; }

	const SDL_Color& GetBackgroundColor() const { return m_clearColor; }
	void SetBackgroundColor(const SDL_Color& color) { m_clearColor = color; }

private:
	SDL_Renderer* m_Renderer{};
	SDL_Window* m_Window{};
	SDL_Color m_clearColor{};
};