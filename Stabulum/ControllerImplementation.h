#pragma once
#include "ControllerButtons.h"

class ControllerImplementation final
{
public:
	ControllerImplementation(int id);
	~ControllerImplementation();

	using XInputController = unsigned int;

	bool Update();

	bool IsPressed(unsigned int button) const;
	bool IsDownThisFrame(unsigned int button) const;
	bool IsUpThisFrame(unsigned int button) const;

	unsigned int ConvertButton(ApplicationController button);

private:
	class Implementation;
	Implementation* m_pImpl;
};