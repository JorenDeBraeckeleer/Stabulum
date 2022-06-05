#include "StabulumPCH.h"
#include "PreviousSceneCommand.h"

#include "SceneManager.h"

PreviousSceneCommand::PreviousSceneCommand()
	: BaseCommand()
{
}

void PreviousSceneCommand::Execute()
{
	SceneManager::GetInstance().LoadPreviousScene();
}
