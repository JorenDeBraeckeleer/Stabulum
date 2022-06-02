#pragma once
#include "BaseComponent.h"

#include "Renderer.h"

class Texture2D;
class TransformComponent;
class TextureTransformComponent;

class RenderComponent final : public BaseComponent
{
public:
	RenderComponent(TransformComponent* pTransformComponent, const std::string& filename = "");

	virtual ~RenderComponent() = default;
	RenderComponent(const RenderComponent& other) = delete;
	RenderComponent(RenderComponent&& other) = delete;
	RenderComponent& operator=(const RenderComponent& other) = delete;
	RenderComponent& operator=(RenderComponent&& other) = delete;

	virtual void Update() override;
	virtual void Render() const override;

	std::shared_ptr<Texture2D> GetTexture() { return m_spTexture; }

	void SetTexture(const std::string& filename);
	void SetTexture(std::shared_ptr<Texture2D> spTexture);

	void SetAllignment(const Renderer::Allign& allignment);

private:
	TransformComponent* m_pTransformComponent;
	TextureTransformComponent* m_pTextureTransformComponent;

	std::shared_ptr<Texture2D> m_spTexture{};

	Renderer::Allign m_Allignment;
};