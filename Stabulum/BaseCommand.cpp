#include "StabulumPCH.h"
#include "BaseCommand.h"

BaseCommand::BaseCommand()
	: m_pGameObject{ nullptr }
{
}

BaseCommand::BaseCommand(GameObject* pGameObject)
	: m_pGameObject{ pGameObject }
{
}