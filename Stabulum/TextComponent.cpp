#include "StabulumPCH.h"
#include "TextComponent.h"

#include <SDL_ttf.h>

#include "Font.h"
#include "RenderComponent.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "Texture2D.h"
#include "TransformComponent.h"

TextComponent::TextComponent(RenderComponent* pRenderComponent, const std::shared_ptr<Font>& font, const RGBColor color, const std::string& text)
	: m_pRenderComponent{ pRenderComponent }
	, m_IsUpdateNeeded{ true }
	, m_Color{ color }
	, m_Text{ text }
	, m_spFont{ font }
{
}

TextComponent::TextComponent(RenderComponent* pRenderComponent, const std::string& fontFilename, unsigned int fontSize, const RGBColor color, const std::string& text)
	: TextComponent(pRenderComponent, nullptr, color, text)
{
	m_spFont = ResourceManager::GetInstance().LoadFont(fontFilename, fontSize);
}

void TextComponent::Update()
{
	if (m_IsUpdateNeeded)
	{
		if (!m_Text.empty() && m_spFont)
		{
			const auto surf = TTF_RenderText_Blended(m_spFont->GetFont(), m_Text.c_str(), Convert::RGBtoSDL(m_Color));

			if (surf == nullptr)
			{
				throw std::runtime_error(std::string("Render text failed: ") + SDL_GetError());
			}

			auto texture = SDL_CreateTextureFromSurface(Renderer::GetInstance().GetSDLRenderer(), surf);

			if (texture == nullptr)
			{
				throw std::runtime_error(std::string("Create text texture from surface failed: ") + SDL_GetError());
			}

			SDL_FreeSurface(surf);

			m_pRenderComponent->SetTexture(std::make_shared<Texture2D>(texture));

			m_IsUpdateNeeded = false;
		}
	}
}

TextComponent* TextComponent::SetText(const std::string& text)
{
	m_Text = text;
	m_IsUpdateNeeded = true;

	return this;
}

TextComponent* TextComponent::SetFont(const std::shared_ptr<Font>& font)
{
	m_spFont = font;
	m_IsUpdateNeeded = true;

	return this;
}

TextComponent* TextComponent::SetColor(const RGBColor color)
{
	m_Color = color;
	m_IsUpdateNeeded = true;

	return this;
}