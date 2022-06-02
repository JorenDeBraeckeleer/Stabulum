#include "StabulumPCH.h"
#include "InputManager.h"
#include "Application.h"
#include <set>

InputManager::InputManager()
	: m_ControllerCount{ 4 }
	, m_Controllers{}
	, m_pKeyboard{ new Keyboard{} }
{
	for (int id{}; id < m_ControllerCount; ++id)
	{
		m_Controllers.push_back(new Controller(id));
	}
}

InputManager::~InputManager()
{
	delete m_pKeyboard;
	m_pKeyboard = nullptr;

	for (Controller* pController : m_Controllers)
	{
		delete pController;
		pController = nullptr;
	}
}

bool InputManager::ProcessInput()
{
	if (Application::HasQuit)
	{
		return false;
	}

	m_pKeyboard->ProcessInput();

	for (Controller* pController : m_Controllers)
	{
		pController->ProcessInput();
	}

	SDL_Event e;
	while (SDL_PollEvent(&e)) {
		if (e.type == SDL_QUIT) {
			return false;
		}
	}

	return true;
}

void InputManager::HandleInput() const
{
	//Keyboard
	auto keyboardCommands{ m_pKeyboard->GetConsoleCommands() };

	std::set<unsigned int> coveredKeyboardButtons{};

	for (const auto& command : *keyboardCommands)
	{
		if (coveredKeyboardButtons.contains(command.Button))
		{
			continue;
		}

		coveredKeyboardButtons.insert(command.Button);

		switch (command.InputState)
		{
		case InputState::Down:
			if (m_pKeyboard->IsDownThisFrame(command.Button))
			{
				HandleCommandExecution(keyboardCommands, command.Button);
			}
			break;
		case InputState::Up:
			if (m_pKeyboard->IsUpThisFrame(command.Button))
			{
				HandleCommandExecution(keyboardCommands, command.Button);
			}
			break;
		case InputState::Pressed:
			if (m_pKeyboard->IsPressed(command.Button))
			{
				HandleCommandExecution(keyboardCommands, command.Button);
			}
			break;
		default:
			std::cout << "Wrong input mode." << std::endl;
			break;
		}
	}

	//Controllers
	for (Controller* pController : m_Controllers)
	{
		if (!pController->IsConnected())
		{
			continue;
		}

		auto controllerCommands{ pController->GetConsoleCommands() };

		std::set<unsigned int> coveredControllerButtons{};

		for (const auto& command : *controllerCommands)
		{
			if (coveredControllerButtons.contains(command.Button))
			{
				continue;
			}

			coveredControllerButtons.insert(command.Button);

			switch (command.InputState)
			{
			case InputState::Down:
				if (pController->IsDownThisFrame(command.Button))
				{
					HandleCommandExecution(controllerCommands, command.Button);
				}
				break;
			case InputState::Up:
				if (pController->IsUpThisFrame(command.Button))
				{
					HandleCommandExecution(controllerCommands, command.Button);
				}
				break;
			case InputState::Pressed:
				if (pController->IsPressed(command.Button))
				{
					HandleCommandExecution(controllerCommands, command.Button);
				}
				break;
			default:
				std::cout << "Wrong input mode." << std::endl;
				break;
			}
		}
	}
}

void InputManager::HandleCommandExecution(std::vector<InputCommand>* pCommands, const unsigned int button) const
{
	for (const auto& command : *pCommands)
	{
		if (button == command.Button)
		{
			for (const auto& action : command.spCommands)
			{
				action->Execute();
			}

			for (const auto& action : command.pCommands)
			{
				action->Execute();
			}

			return;
		}
	}
}

void InputManager::AddBindingToKeyboard(std::shared_ptr<BaseCommand> spCommand, ApplicationKeyboard button, InputState inputState)
{
	m_pKeyboard->AddConsoleCommand(spCommand, button, inputState);
}

void InputManager::RemoveBindingFromKeyboard(ApplicationKeyboard button)
{
	m_pKeyboard->RemoveConsoleCommand(button);
}

void InputManager::AddBindingToController(std::shared_ptr<BaseCommand> spCommand, ApplicationController button, InputState inputState)
{
	for (Controller* pController : m_Controllers)
	{
		pController->AddConsoleCommand(spCommand, button, inputState);
	}
}

void InputManager::AddBindingToController(std::shared_ptr<BaseCommand> spCommand, ApplicationController button, InputState inputState, int controllerId)
{
	if (m_ControllerCount > controllerId && controllerId >= 0)
	{
		m_Controllers.at(controllerId)->AddConsoleCommand(spCommand, button, inputState);
	}
	else
	{
		std::cout << "Invalid controller-id for binding." << std::endl;
	}
}

void InputManager::RemoveBindingFromController(ApplicationController button)
{
	for (Controller* pController : m_Controllers)
	{
		pController->RemoveConsoleCommand(button);
	}
}

void InputManager::RemoveBindingFromController(ApplicationController button, int controllerId)
{
	if (m_ControllerCount > controllerId && controllerId >= 0)
	{
		m_Controllers[controllerId]->RemoveConsoleCommand(button);
	}
	else
	{
		std::cout << "Invalid controller-id for binding." << std::endl;
	}
}

void InputManager::AddBindingToController(std::shared_ptr<BaseCommand> spCommand, PS4Controller button, InputState inputState)
{
	AddBindingToController(spCommand, ConvertButton(button), inputState);
}

void InputManager::AddBindingToController(std::shared_ptr<BaseCommand> spCommand, PS4Controller button, InputState inputState, int controllerId)
{
	AddBindingToController(spCommand, ConvertButton(button), inputState, controllerId);
}

void InputManager::AddBindingToController(std::shared_ptr<BaseCommand> spCommand, XBoxController button, InputState inputState)
{
	AddBindingToController(spCommand, ConvertButton(button), inputState);
}

void InputManager::AddBindingToController(std::shared_ptr<BaseCommand> spCommand, XBoxController button, InputState inputState, int controllerId)
{
	AddBindingToController(spCommand, ConvertButton(button), inputState, controllerId);
}

void InputManager::AddBindingToController(std::shared_ptr<BaseCommand> spCommand, SwitchController button, InputState inputState)
{
	AddBindingToController(spCommand, ConvertButton(button), inputState);
}

void InputManager::AddBindingToController(std::shared_ptr<BaseCommand> spCommand, SwitchController button, InputState inputState, int controllerId)
{
	AddBindingToController(spCommand, ConvertButton(button), inputState, controllerId);
}

void InputManager::RemoveBindingFromController(PS4Controller button)
{
	RemoveBindingFromController(ConvertButton(button));
}

void InputManager::RemoveBindingFromController(PS4Controller button, int controllerId)
{
	RemoveBindingFromController(ConvertButton(button), controllerId);
}

void InputManager::RemoveBindingFromController(XBoxController button)
{
	RemoveBindingFromController(ConvertButton(button));
}

void InputManager::RemoveBindingFromController(XBoxController button, int controllerId)
{
	RemoveBindingFromController(ConvertButton(button), controllerId);
}

void InputManager::RemoveBindingFromController(SwitchController button)
{
	RemoveBindingFromController(ConvertButton(button));
}

void InputManager::RemoveBindingFromController(SwitchController button, int controllerId)
{
	RemoveBindingFromController(ConvertButton(button), controllerId);
}

ApplicationController InputManager::ConvertButton(PS4Controller button)
{
	switch (button)
	{
	case PS4Controller::DPadUp:
		return ApplicationController::DPadNorth;
		break;
	case PS4Controller::DPadDown:
		return ApplicationController::DPadSouth;
		break;
	case PS4Controller::DPadLeft:
		return ApplicationController::DPadWest;
		break;
	case PS4Controller::DPadRight:
		return ApplicationController::DPadEast;
		break;
	case PS4Controller::Options:
		return ApplicationController::SpecialButtonRight;
		break;
	case PS4Controller::Share:
		return ApplicationController::SpecialButtonLeft;
		break;
	case PS4Controller::L3:
		return ApplicationController::ThumbstickLeft;
		break;
	case PS4Controller::R3:
		return ApplicationController::ThumbstickRight;
		break;
	case PS4Controller::L1:
		return ApplicationController::BumperLeft;
		break;
	case PS4Controller::R1:
		return ApplicationController::BumperRight;
		break;
	case PS4Controller::Cross:
		return ApplicationController::ButtonSouth;
		break;
	case PS4Controller::Circle:
		return ApplicationController::ButtonEast;
		break;
	case PS4Controller::Square:
		return ApplicationController::ButtonWest;
		break;
	case PS4Controller::Triangle:
		return ApplicationController::ButtonNorth;
		break;
	default:
		break;
	}

	return ApplicationController();
}

ApplicationController InputManager::ConvertButton(XBoxController button)
{
	switch (button)
	{
	case XBoxController::DPadUp:
		return ApplicationController::DPadNorth;
		break;
	case XBoxController::DPadDown:
		return ApplicationController::DPadSouth;
		break;
	case XBoxController::DPadLeft:
		return ApplicationController::DPadWest;
		break;
	case XBoxController::DPadRight:
		return ApplicationController::DPadEast;
		break;
	case XBoxController::Start:
		return ApplicationController::SpecialButtonRight;
		break;
	case XBoxController::Back:
		return ApplicationController::SpecialButtonLeft;
		break;
	case XBoxController::LeftStickButton:
		return ApplicationController::ThumbstickLeft;
		break;
	case XBoxController::RightStickButton:
		return ApplicationController::ThumbstickRight;
		break;
	case XBoxController::LeftBumper:
		return ApplicationController::BumperLeft;
		break;
	case XBoxController::RightBumper:
		return ApplicationController::BumperRight;
		break;
	case XBoxController::A:
		return ApplicationController::ButtonSouth;
		break;
	case XBoxController::B:
		return ApplicationController::ButtonEast;
		break;
	case XBoxController::X:
		return ApplicationController::ButtonWest;
		break;
	case XBoxController::Y:
		return ApplicationController::ButtonNorth;
		break;
	default:
		break;
	}

	return ApplicationController();
}

ApplicationController InputManager::ConvertButton(SwitchController button)
{
	switch (button)
	{
	case SwitchController::DirectionalUp:
		return ApplicationController::DPadNorth;
		break;
	case SwitchController::DirectionalDown:
		return ApplicationController::DPadSouth;
		break;
	case SwitchController::DirectionalLeft:
		return ApplicationController::DPadWest;
		break;
	case SwitchController::DirectionalRight:
		return ApplicationController::DPadEast;
		break;
	case SwitchController::Plus:
		return ApplicationController::SpecialButtonRight;
		break;
	case SwitchController::Minus:
		return ApplicationController::SpecialButtonLeft;
		break;
	case SwitchController::LeftStickButton:
		return ApplicationController::ThumbstickLeft;
		break;
	case SwitchController::RightStickButton:
		return ApplicationController::ThumbstickRight;
		break;
	case SwitchController::L:
		return ApplicationController::BumperLeft;
		break;
	case SwitchController::R:
		return ApplicationController::BumperRight;
		break;
	case SwitchController::B:
		return ApplicationController::ButtonSouth;
		break;
	case SwitchController::A:
		return ApplicationController::ButtonEast;
		break;
	case SwitchController::Y:
		return ApplicationController::ButtonWest;
		break;
	case SwitchController::X:
		return ApplicationController::ButtonNorth;
		break;
	default:
		break;
	}

	return ApplicationController();
}