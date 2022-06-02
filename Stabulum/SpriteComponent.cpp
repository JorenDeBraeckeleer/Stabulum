#include "StabulumPCH.h"
#include "SpriteComponent.h"

#include "Texture2D.h"
#include "RenderComponent.h"
#include "TextureTransformComponent.h"
#include "TimeManager.h"

SpriteComponent::SpriteComponent(RenderComponent* pRenderComponent, TextureTransformComponent* pTextureTransformComponent, int rows, int collumns)
	: m_pRenderComponent{ pRenderComponent }
	, m_pTextureTransformComponent{ pTextureTransformComponent }
	, m_Rows{ rows }
	, m_Collumns{ collumns }
	, m_Width{}
	, m_Height{}
	, m_TextureWidth{}
	, m_TextureHeight{}
	, m_IsMoving{}
	, m_CurrentRow{ 1 }
	, m_CurrentCollumn{ 1 }
	, m_FramesPerSecond{ 12 }
	, m_TotalTime{}
	, m_AnimationTime{ 1.f / m_FramesPerSecond }
{
	SDL_QueryTexture((*m_pRenderComponent->GetTexture()).GetSDLTexture(), nullptr, nullptr, &m_TextureWidth, &m_TextureHeight);

	m_Width = m_TextureWidth / m_Collumns;
	m_Height = m_TextureHeight / m_Rows;

	m_pTextureTransformComponent->SetSize(m_Width, m_Height);
}

void SpriteComponent::Update()
{
	if (m_IsMoving)
	{
		m_TotalTime += TimeManager::DeltaTime;
		if (m_AnimationTime < m_TotalTime)
		{
			++m_CurrentCollumn;

			if (m_CurrentCollumn == m_Collumns)
			{
				m_CurrentCollumn = 0;
			}

			m_TotalTime -= m_AnimationTime;
		}

		m_pTextureTransformComponent->SetPosition(m_CurrentCollumn * m_Width, m_CurrentRow * m_Height);
	}
	else
	{
		m_pTextureTransformComponent->SetPosition(m_CurrentCollumn * m_Width, m_CurrentRow * m_Height);
	}
}