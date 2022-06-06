#include "BurgerTimePCH.h"
#include "SceneBackwardCommand.h"

#include "SceneManager.h"
#include "Scene.h"
#include "ScoreComponent.h"

SceneBackwardCommand::SceneBackwardCommand()
	: BaseCommand()
{
}

void SceneBackwardCommand::Execute()
{
	SceneManager& sceneManager = SceneManager::GetInstance();
	int score = sceneManager.GetActiveScene()->FindComponent<ScoreComponent>()->GetScore();
	sceneManager.LoadPreviousScene();
	sceneManager.GetActiveScene()->FindComponent<ScoreComponent>()->SetScore(score);
}
