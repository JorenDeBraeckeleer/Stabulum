#include "StabulumPCH.h"
#include "Controller.h"

#include "ControllerImplementation.h"

Controller::Controller(int id)
	: m_pImpl{ new ControllerImplementation(id) }
	, m_ConsoleCommands{}
	, m_ControllerIndex{ id }
	, m_CurrentConnectionState{ ConnectionState::Disconnected }
	, m_PreviousConnectionState{}
{
	m_PreviousConnectionState = m_CurrentConnectionState;
}

Controller::~Controller()
{
	delete m_pImpl;
	m_pImpl = nullptr;

	for (auto& command : m_ConsoleCommands)
	{
		for (auto& action : command.pCommands)
		{
			delete action;
			action = nullptr;
		}
	}
}

void Controller::ProcessInput()
{
	if (m_pImpl->Update())
	{
		m_CurrentConnectionState = ConnectionState::Connected;
	}
	else
	{
		m_CurrentConnectionState = ConnectionState::Disconnected;
	}

	UpdateConnectionState();
}

bool Controller::IsConnected() const
{
	if (m_CurrentConnectionState == ConnectionState::Connected)
	{
		return true;
	}

	return false;
}

bool Controller::IsPressed(XInputController button) const
{
	return m_pImpl->IsPressed(button);
}

bool Controller::IsDownThisFrame(XInputController button) const
{
	return m_pImpl->IsDownThisFrame(button);
}

bool Controller::IsUpThisFrame(XInputController button) const
{
	return m_pImpl->IsUpThisFrame(button);
}

void Controller::AddConsoleCommand(std::shared_ptr<BaseCommand> spCommand, ApplicationController button, InputState inputState)
{
	XInputController convertedButton{ GetConvertedButton(button) };

	for (auto& command : m_ConsoleCommands)
	{
		if (convertedButton == command.Button)
		{
			command.spCommands.push_back(spCommand);
			return;
		}
	}

	InputCommand controllerCommand{};
	controllerCommand.Button = convertedButton;
	controllerCommand.InputState = inputState;
	controllerCommand.spCommands.push_back(spCommand);
	m_ConsoleCommands.push_back(controllerCommand);
}

void Controller::RemoveConsoleCommand(ApplicationController button)
{
	for (auto& command : m_ConsoleCommands)
	{
		if (m_pImpl->ConvertButton(button) == command.Button)
		{
			for (auto& action : command.pCommands)
			{
				delete action;
				action = nullptr;
			}

			command.pCommands.clear();

			return;
		}
	}
}

void Controller::UpdateConnectionState()
{
	if (m_CurrentConnectionState != m_PreviousConnectionState)
	{
		switch (m_CurrentConnectionState)
		{
		case Controller::ConnectionState::Connected:
			std::cout << "Controller " << m_ControllerIndex << " connected." << std::endl;
			break;
		case Controller::ConnectionState::Disconnected:
			std::cout << "Controller " << m_ControllerIndex << " disconnected." << std::endl;
			break;
		default:
			break;
		}

		m_PreviousConnectionState = m_CurrentConnectionState;
	}
}

unsigned int Controller::GetConvertedButton(ApplicationController button)
{
	return m_pImpl->ConvertButton(button);
}