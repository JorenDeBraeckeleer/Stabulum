#pragma once
#include "BaseCommand.h"

class NextSceneCommand final : public BaseCommand
{
public:
	NextSceneCommand();
	virtual ~NextSceneCommand() = default;

	virtual void Execute() override;
};