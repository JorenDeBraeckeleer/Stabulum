#include "BurgerTimePCH.h"
#include "SceneForwardCommand.h"

#include "SceneManager.h"
#include "Scene.h"
#include "ScoreComponent.h"

SceneForwardCommand::SceneForwardCommand()
	: BaseCommand()
{
}

void SceneForwardCommand::Execute()
{
	SceneManager& sceneManager = SceneManager::GetInstance();
	int score = sceneManager.GetActiveScene()->FindComponent<ScoreComponent>()->GetScore();
	sceneManager.LoadNextScene();
	sceneManager.GetActiveScene()->FindComponent<ScoreComponent>()->SetScore(score);
}