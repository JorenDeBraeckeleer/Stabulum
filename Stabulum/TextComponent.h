#pragma once

#include "BaseComponent.h"

#include "Structs.h"

class Font;
class RenderComponent;

class TextComponent final : public BaseComponent
{
public:
	TextComponent(RenderComponent* pRenderComponent, const std::shared_ptr<Font>& font, const RGBColor color = { 255, 255, 255 }, const std::string& text = "");
	TextComponent(RenderComponent* pRenderComponent, const std::string& fontFilename, unsigned int fontSize, const RGBColor color = { 255, 255, 255 }, const std::string& text = "");
	virtual ~TextComponent() = default;

	TextComponent(const TextComponent& other) = delete;
	TextComponent(TextComponent&& other) = delete;
	TextComponent& operator=(const TextComponent& other) = delete;
	TextComponent& operator=(TextComponent&& other) = delete;

	virtual void Update() override;

	TextComponent* SetText(const std::string& text);
	TextComponent* SetFont(const std::shared_ptr<Font>& font);
	TextComponent* SetColor(const RGBColor color);

private:
	RenderComponent* m_pRenderComponent{};

	bool m_IsUpdateNeeded;
	RGBColor m_Color{};
	std::string m_Text{};
	std::shared_ptr<Font> m_spFont{};
};