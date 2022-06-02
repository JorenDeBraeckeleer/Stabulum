#include "StabulumPCH.h"
#include "QuitCommand.h"

#include "Application.h"

QuitCommand::QuitCommand()
	: BaseCommand()
{
}

void QuitCommand::Execute()
{
	Application::HasQuit = true;
}