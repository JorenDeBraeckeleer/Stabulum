#pragma once
#include "BaseComponent.h"

class Transform;

class TextureTransformComponent final : public BaseComponent
{
public:
	TextureTransformComponent(int x, int y, int width, int height);
	TextureTransformComponent(SDL_Rect* pSrcRect);

	virtual ~TextureTransformComponent();
	TextureTransformComponent(const TextureTransformComponent& other) = delete;
	TextureTransformComponent(TextureTransformComponent&& other) = delete;
	TextureTransformComponent& operator=(const TextureTransformComponent& other) = delete;
	TextureTransformComponent& operator=(TextureTransformComponent&& other) = delete;

	virtual void Update() override;

	void SetRect(SDL_Rect* pSrcRect);
	void SetPosition(int x, int y);
	void SetSize(int width, int height);
	SDL_Rect* GetRect() { return m_pRect; }

private:
	SDL_Rect* m_pRect;
};