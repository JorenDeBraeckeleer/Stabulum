#pragma once
#include "BaseCommand.h"

class QuitCommand final : public BaseCommand
{
public:
	QuitCommand();
	virtual ~QuitCommand() = default;

	virtual void Execute() override;
};