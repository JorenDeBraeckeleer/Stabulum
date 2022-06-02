#pragma once
#include "BaseComponent.h"

class PeterPepperComponent final : public BaseComponent, public Subject
{
public:
	PeterPepperComponent(int nrLives = 5);

	virtual ~PeterPepperComponent() = default;
	PeterPepperComponent(const PeterPepperComponent& other) = delete;
	PeterPepperComponent(PeterPepperComponent&& other) = delete;
	PeterPepperComponent& operator=(const PeterPepperComponent& other) = delete;
	PeterPepperComponent& operator=(PeterPepperComponent&& other) = delete;

	virtual void Update() override;

	void LostLife();

	int GetNrLives() { return m_NrLives; }

private:
	int m_NrLives;
	bool m_IsDead;
	bool m_IsUpdateNeeded;
};