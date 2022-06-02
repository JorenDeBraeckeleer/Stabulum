#include "StabulumPCH.h"
#include "TextureTransformComponent.h"

TextureTransformComponent::TextureTransformComponent(int x, int y, int width, int height)
	: m_pRect{ new SDL_Rect{} }
{
	m_pRect->x = x;
	m_pRect->y = y;
	m_pRect->w = width;
	m_pRect->h = height;
}

TextureTransformComponent::TextureTransformComponent(SDL_Rect* pSrcRect)
	: m_pRect{ pSrcRect }
{
}

TextureTransformComponent::~TextureTransformComponent()
{
	delete m_pRect;
	m_pRect = nullptr;
}

void TextureTransformComponent::Update()
{
}

void TextureTransformComponent::SetRect(SDL_Rect* pSrcRect)
{
	m_pRect = pSrcRect;
}

void TextureTransformComponent::SetPosition(int x, int y)
{
	m_pRect->x = x;
	m_pRect->y = y;
}

void TextureTransformComponent::SetSize(int width, int height)
{
	m_pRect->w = width;
	m_pRect->h = height;
}