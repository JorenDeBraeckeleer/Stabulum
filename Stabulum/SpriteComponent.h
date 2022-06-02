#pragma once
#include "BaseComponent.h"

class Texture2D;
class RenderComponent;
class TextureTransformComponent;

class SpriteComponent final : public BaseComponent
{
public:
	SpriteComponent(RenderComponent* pRenderComponent, TextureTransformComponent* pTextureTransformComponent, int rows, int collumns);

	virtual ~SpriteComponent() = default;
	SpriteComponent(const SpriteComponent& other) = delete;
	SpriteComponent(SpriteComponent&& other) = delete;
	SpriteComponent& operator=(const SpriteComponent& other) = delete;
	SpriteComponent& operator=(SpriteComponent&& other) = delete;

	virtual void Update() override;

	void SetCurrentRow(int row) { m_CurrentRow = row; }
	void SetCurrentCollumn(int collumn) { m_CurrentCollumn = collumn; }
	void SetIsMoving(bool isMoving) { m_IsMoving = isMoving; }

private:
	RenderComponent* m_pRenderComponent;
	TextureTransformComponent* m_pTextureTransformComponent;

	int m_Rows, m_Collumns;
	int m_Width, m_Height, m_TextureWidth, m_TextureHeight;

	bool m_IsMoving;
	int m_CurrentRow, m_CurrentCollumn;

	int m_FramesPerSecond;
	float m_TotalTime, m_AnimationTime;
};