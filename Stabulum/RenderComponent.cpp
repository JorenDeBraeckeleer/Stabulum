#include "StabulumPCH.h"
#include "RenderComponent.h"
#include "ResourceManager.h"

#include "TransformComponent.h"
#include "TextureTransformComponent.h"

RenderComponent::RenderComponent(TransformComponent* pTransformComponent, const int layer, const std::string& filename)
	: m_pTransformComponent{ pTransformComponent }
	, m_pTextureTransformComponent{ nullptr }
	, m_spTexture{ nullptr }
	, m_Allignment{ Renderer::Allign::TopLeft }
	, m_Layer{ layer }
{
	if (!filename.empty())
	{
		m_spTexture = ResourceManager::GetInstance().LoadTexture(filename);
	}
}

void RenderComponent::Update()
{
	//Initialize component once
	if (!m_pTextureTransformComponent)
	{
		if (TextureTransformComponent* pTextTransformComponent = m_pGameObject->GetComponent<TextureTransformComponent>())
		{
			m_pTextureTransformComponent = pTextTransformComponent;
		}
	}
}
#include "../BurgerTime/BurgerPartComponent.h"
void RenderComponent::Render() const
{
	if (m_spTexture)
	{
		const auto& pos = m_pTransformComponent->GetPixelPosition();
		
		//Use TextureTransformComponent if available
		if (m_pTextureTransformComponent)
		{
			Renderer::GetInstance().RenderTexture(*m_spTexture, m_pTextureTransformComponent->GetRect(), pos.x, pos.y, m_Allignment, m_Layer);
			return;
		}

		Renderer::GetInstance().RenderTexture(*m_spTexture, pos.x, pos.y, m_Allignment, m_Layer);
	}
}

void RenderComponent::SetTexture(const std::string& filename)
{
	m_spTexture = ResourceManager::GetInstance().LoadTexture(filename);
}

void RenderComponent::SetTexture(std::shared_ptr<Texture2D> spTexture)
{
	m_spTexture = spTexture;
}

void RenderComponent::SetAllignment(const Renderer::Allign& allignment)
{
	m_Allignment = allignment;
}