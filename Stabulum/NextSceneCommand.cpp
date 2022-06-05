#include "StabulumPCH.h"
#include "NextSceneCommand.h"

#include "SceneManager.h"

NextSceneCommand::NextSceneCommand()
	: BaseCommand()
{
}

void NextSceneCommand::Execute()
{
	SceneManager::GetInstance().LoadNextScene();
}