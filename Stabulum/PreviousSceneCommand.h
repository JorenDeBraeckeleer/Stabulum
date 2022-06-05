#pragma once
#include "BaseCommand.h"

class PreviousSceneCommand final : public BaseCommand
{
public:
	PreviousSceneCommand();
	virtual ~PreviousSceneCommand() = default;

	virtual void Execute() override;
};