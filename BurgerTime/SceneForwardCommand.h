#pragma once
#include "BaseCommand.h"

class SceneForwardCommand final : public BaseCommand
{
public:
	SceneForwardCommand();
	virtual ~SceneForwardCommand() = default;

	virtual void Execute() override;
};