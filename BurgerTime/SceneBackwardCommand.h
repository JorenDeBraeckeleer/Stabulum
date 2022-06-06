#pragma once
#include "BaseCommand.h"

class SceneBackwardCommand final : public BaseCommand
{
public:
	SceneBackwardCommand();
	virtual ~SceneBackwardCommand() = default;

	virtual void Execute() override;
};