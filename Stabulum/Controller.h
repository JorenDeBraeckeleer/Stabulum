#pragma once
#include "BaseCommand.h"
#include "ControllerButtons.h"

//This is not the real pImpl, this class can be foward declared here
class ControllerImplementation;

class Controller final
{
public:
	Controller(int id);

	~Controller();
	Controller(const Controller& other) = delete;
	Controller(Controller&& other) = delete;
	Controller& operator=(const Controller& other) = delete;
	Controller& operator=(Controller&& other) = delete;

	using XInputController = unsigned int;

	struct ControllerCommand
	{
	public:
		XInputController Button{};
		InputState InputState{};
		std::vector<BaseCommand*> pCommands{};
		std::vector<std::shared_ptr<BaseCommand>> spCommands{};
	};

	std::vector<ControllerCommand>* GetConsoleCommands() { return &m_ConsoleCommands; }

	void ProcessInput();

	bool IsConnected() const;

	bool IsPressed(XInputController button) const;
	bool IsDownThisFrame(XInputController button) const;
	bool IsUpThisFrame(XInputController button) const;

	template<typename myType>
	void AddConsoleCommand(ApplicationController button, InputState inputState);

	void AddConsoleCommand(std::shared_ptr<BaseCommand> spCommand, ApplicationController button, InputState inputState);

	template<typename myType>
	void RemoveConsoleCommand(ApplicationController button);

	void RemoveConsoleCommand(ApplicationController button);

private:
	enum class ConnectionState
	{
		Connected,
		Disconnected,
	};

	void UpdateConnectionState();
	unsigned int GetConvertedButton(ApplicationController button);

	ControllerImplementation* m_pImpl;

	std::vector<ControllerCommand> m_ConsoleCommands{};
	int m_ControllerIndex;
	ConnectionState m_CurrentConnectionState, m_PreviousConnectionState;
};

template<typename myType>
inline void Controller::AddConsoleCommand(ApplicationController button, InputState inputState)
{
	XInputController convertedButton{ GetConvertedButton(button) };

	for (auto& command : m_ConsoleCommands)
	{
		if (convertedButton == command.Button)
		{
			command.pCommands.push_back(new myType());
			return;
		}
	}

	ControllerCommand controllerCommand{};
	controllerCommand.Button = convertedButton;
	controllerCommand.InputState = inputState;
	controllerCommand.pCommands.push_back(new myType());
	m_ConsoleCommands.push_back(controllerCommand);
}

template<typename myType>
inline void Controller::RemoveConsoleCommand(ApplicationController button)
{
	for (auto& command : m_ConsoleCommands)
	{
		if (GetConvertedButton(button) == command.Button)
		{
			for (int idx{}; idx < command.pCommands.size(); ++idx)
			{
				if (dynamic_cast<myType*>(command.pCommands[idx]))
				{
					delete command.pCommands[idx];
					command.pCommands[idx] = nullptr;

					command.pCommands.erase(command.pCommands.begin() + idx);
				}
			}

			return;
		}
	}
}