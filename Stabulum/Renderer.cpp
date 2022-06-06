#include "StabulumPCH.h"
#include "Renderer.h"

#include "SceneManager.h"
#include "Texture2D.h"

int GetOpenGLDriverIndex()
{
	auto openglIndex = -1;
	const auto driverCount = SDL_GetNumRenderDrivers();
	for (auto i = 0; i < driverCount; i++)
	{
		SDL_RendererInfo info;
		if (!SDL_GetRenderDriverInfo(i, &info))
			if (!strcmp(info.name, "opengl"))
				openglIndex = i;
	}
	return openglIndex;
}

void Renderer::Init(SDL_Window * window)
{
	m_Window = window;
	m_Renderer = SDL_CreateRenderer(window, GetOpenGLDriverIndex(), SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (m_Renderer == nullptr) 
	{
		throw std::runtime_error(std::string("SDL_CreateRenderer Error: ") + SDL_GetError());
	}
}

void Renderer::Render() const
{
	const auto& color = GetBackgroundColor();
	SDL_SetRenderDrawColor(m_Renderer, color.r, color.g, color.b, color.a);
	SDL_RenderClear(m_Renderer);

	//Clear layers
	for (Layer* pLayer : m_pLayers)
	{
		SDL_SetRenderDrawColor(m_Renderer, 0, 0, 0, 0);
		SDL_SetRenderTarget(m_Renderer, pLayer->GetTexture());
		SDL_RenderFillRect(m_Renderer, nullptr);
	}

	SceneManager::GetInstance().Render();
	
	//Fill layers
	for (Layer* pLayer : m_pLayers)
	{
		SDL_RenderCopy(m_Renderer, pLayer->GetTexture(), nullptr, nullptr);
	}

	SDL_RenderPresent(m_Renderer);
}

void Renderer::Destroy()
{
	for (Layer* pLayer : m_pLayers)
	{
		delete pLayer;
		pLayer = nullptr;
	}

	if (m_Renderer != nullptr)
	{
		SDL_DestroyRenderer(m_Renderer);
		m_Renderer = nullptr;
	}
}

void Renderer::RenderTexture(const Texture2D& texture, const float x, const float y, const Allign& allignment, int layer) const
{
	SDL_Rect dst{};
	dst.x = static_cast<int>(x);
	dst.y = static_cast<int>(y);
	SDL_QueryTexture(texture.GetSDLTexture(), nullptr, nullptr, &dst.w, &dst.h);

	if (allignment != Allign::TopLeft)
	{
		AllignmentCheck(texture, dst.x, dst.y, allignment);
	}

	//Set correct layer
	SDL_SetRenderTarget(GetSDLRenderer(), m_pLayers[layer]->GetTexture());

	SDL_RenderCopy(GetSDLRenderer(), texture.GetSDLTexture(), nullptr, &dst);

	//Set layer back
	SDL_SetRenderTarget(GetSDLRenderer(), nullptr);
}

void Renderer::RenderTexture(const Texture2D& texture, const float x, const float y, const float width, const float height, const Allign& allignment, int layer) const
{
	SDL_Rect dst{};
	dst.x = static_cast<int>(x);
	dst.y = static_cast<int>(y);
	dst.w = static_cast<int>(width);
	dst.h = static_cast<int>(height);

	if (allignment != Allign::TopLeft)
	{
		AllignmentCheck(texture, dst.x, dst.y, allignment);
	}

	//Set correct layer
	SDL_SetRenderTarget(GetSDLRenderer(), m_pLayers[layer]->GetTexture());

	SDL_RenderCopy(GetSDLRenderer(), texture.GetSDLTexture(), nullptr, &dst);

	//Set layer back
	SDL_SetRenderTarget(GetSDLRenderer(), nullptr);
}

void Renderer::RenderTexture(const Texture2D& texture, float srcX, float srcY, float srcWidth, float srcHeight, float dstX, float dstY, const Allign& allignment, int layer) const
{
	SDL_Rect src{};
	src.x = static_cast<int>(srcX);
	src.y = static_cast<int>(srcY);
	src.w = static_cast<int>(srcWidth);
	src.h = static_cast<int>(srcHeight);

	SDL_Rect dst{};
	dst.x = static_cast<int>(dstX);
	dst.y = static_cast<int>(dstY);
	dst.w = static_cast<int>(srcWidth);
	dst.h = static_cast<int>(srcHeight);

	if (allignment != Allign::TopLeft)
	{
		AllignmentCheck(texture, dst.x, dst.y, allignment, &src);
	}

	//Set correct layer
	SDL_SetRenderTarget(GetSDLRenderer(), m_pLayers[layer]->GetTexture());

	SDL_RenderCopy(GetSDLRenderer(), texture.GetSDLTexture(), &src, &dst);

	//Set layer back
	SDL_SetRenderTarget(GetSDLRenderer(), nullptr);
}

void Renderer::RenderTexture(const Texture2D& texture, SDL_Rect* pSrcRect, float dstX, float dstY, const Allign& allignment, int layer) const
{
	SDL_Rect dst{};
	dst.x = static_cast<int>(dstX);
	dst.y = static_cast<int>(dstY);
	dst.w = static_cast<int>(pSrcRect->w);
	dst.h = static_cast<int>(pSrcRect->h);

	if (allignment != Allign::TopLeft)
	{
		AllignmentCheck(texture, dst.x, dst.y, allignment, pSrcRect);
	}

	//Set correct layer
	SDL_SetRenderTarget(GetSDLRenderer(), m_pLayers[layer]->GetTexture());

	SDL_RenderCopy(GetSDLRenderer(), texture.GetSDLTexture(), pSrcRect, &dst);

	//Set layer back
	SDL_SetRenderTarget(GetSDLRenderer(), nullptr);
}

void Renderer::AllignmentCheck(const Texture2D& texture, int& dstX, int& dstY, const Allign& allignment, SDL_Rect* pSrcRect) const
{
	int textureWidth{}, textureHeight{};

	if (pSrcRect)
	{
		textureWidth = pSrcRect->w;
		textureHeight = pSrcRect->h;
	}
	else
	{
		SDL_QueryTexture(texture.GetSDLTexture(), nullptr, nullptr, &textureWidth, &textureHeight);
	}

	switch (allignment)
	{
	case Allign::BottomLeft:
		dstY -= textureHeight;
		break;
	case Allign::BottomRight:
		dstX -= textureWidth;
		dstY -= textureHeight;
		break;
	case Allign::TopRight:
		dstX -= textureWidth;
		break;
	default:
		break;
	}
}

void Renderer::AddLayer()
{
	int width{}, height{};
	SDL_GetWindowSize(m_Window, &width, &height);
	float scaleX{}, scaleY{};
	SDL_RenderGetScale(m_Renderer, &scaleX, &scaleY);

	SDL_Texture* pLayer = SDL_CreateTexture(m_Renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, int(width / scaleX), int(height / scaleY));
	SDL_SetTextureBlendMode(pLayer, SDL_BLENDMODE_BLEND);

	m_pLayers.emplace_back(new Layer{ pLayer });
}