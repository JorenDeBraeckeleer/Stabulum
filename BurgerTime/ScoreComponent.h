#pragma once
#include "BaseComponent.h"

class ScoreComponent final : public BaseComponent, public Observer
{
public:
	ScoreComponent(int score = 0);

	virtual ~ScoreComponent() = default;
	ScoreComponent(const ScoreComponent& other) = delete;
	ScoreComponent(ScoreComponent&& other) = delete;
	ScoreComponent& operator=(const ScoreComponent& other) = delete;
	ScoreComponent& operator=(ScoreComponent&& other) = delete;

	virtual void Update() override;

	virtual void OnNotify(GameObject* pGameObject, const GameEvent& event) override;

	void SetScore(int score) { m_Score = score; }
	int GetScore() { return m_Score; }

private:
	int m_Score;
};