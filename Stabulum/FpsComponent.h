#pragma once

#include "BaseComponent.h"

class TextComponent;

class FpsComponent final : public BaseComponent
{
public:
	FpsComponent(TextComponent* pTextComponent);
	virtual ~FpsComponent() = default;

	FpsComponent(const FpsComponent& other) = delete;
	FpsComponent(FpsComponent&& other) = delete;
	FpsComponent& operator=(const FpsComponent& other) = delete;
	FpsComponent& operator=(FpsComponent&& other) = delete;

	virtual void Update() override;

private:
	TextComponent* m_pTextComponent;
	float m_Timer;
	int m_NrFps;
};