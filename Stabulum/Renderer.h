#pragma once
#include "Singleton.h"

class Texture2D;

//Render order
class Layer final
{
public:
	Layer(SDL_Texture* pTexture)
		: m_pTexture{ pTexture }
	{
	}

	~Layer()
	{
		SDL_DestroyTexture(m_pTexture);
	}

	Layer(const Layer& other) = delete;
	Layer(Layer&& other) noexcept = delete;
	Layer& operator=(const Layer& other) = delete;
	Layer& operator=(Layer&& other) noexcept = delete;

	SDL_Texture* GetTexture() const { return m_pTexture; }

private:
	SDL_Texture* m_pTexture;
};

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

	void RenderTexture(const Texture2D& texture, float x, float y, const Allign& allignment = Allign::TopLeft, int layer = 0) const;
	void RenderTexture(const Texture2D& texture, float x, float y, float width, float height, const Allign& allignment = Allign::TopLeft, int layer = 0) const;
	void RenderTexture(const Texture2D& texture, float srcX, float srcY, float srcWidth, float srcHeight, float dstX, float dstY, const Allign& allignment = Allign::TopLeft, int layer = 0) const;
	void RenderTexture(const Texture2D& texture, SDL_Rect* pSrcRect, float dstX, float dstY, const Allign& allignment = Allign::TopLeft, int layer = 0) const;

	void AllignmentCheck(const Texture2D& texture, int& dstX, int& dstY, const Allign& allignment, SDL_Rect* pSrcRect = nullptr) const;

	SDL_Renderer* GetSDLRenderer() const { return m_Renderer; }

	const SDL_Color& GetBackgroundColor() const { return m_clearColor; }
	void SetBackgroundColor(const SDL_Color& color) { m_clearColor = color; }

	void AddLayer();

private:
	SDL_Renderer* m_Renderer{};
	SDL_Window* m_Window{};
	SDL_Color m_clearColor{};

	std::vector<Layer*> m_pLayers;
};