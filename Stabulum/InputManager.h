#pragma once
#include "Singleton.h"
#include "Controller.h"

class InputManager final : public Singleton<InputManager>
{
public:
	InputManager();

	~InputManager();
	InputManager(const InputManager& other) = delete;
	InputManager(InputManager&& other) = delete;
	InputManager& operator=(const InputManager& other) = delete;
	InputManager& operator=(InputManager&& other) = delete;

	bool ProcessInput();
	void HandleInput() const;

private:
	void HandleCommandExecution(std::vector<Controller::ControllerCommand>* pCommands, const unsigned int command) const;

	const int m_ControllerCount;
	std::vector<Controller*> m_Controllers;

public:
	template<typename myType>
	void AddBindingToController(PS4Controller button, InputState inputState);
	template<typename myType>
	void AddBindingToController(PS4Controller button, InputState inputState, int controllerId);
	template<typename myType>
	void AddBindingToController(XBoxController button, InputState inputState);
	template<typename myType>
	void AddBindingToController(XBoxController button, InputState inputState, int controllerId);
	template<typename myType>
	void AddBindingToController(SwitchController button, InputState inputState);
	template<typename myType>
	void AddBindingToController(SwitchController button, InputState inputState, int controllerId);

	void AddBindingToController(std::shared_ptr<BaseCommand> spCommand, PS4Controller button, InputState inputState);
	void AddBindingToController(std::shared_ptr<BaseCommand> spCommand, PS4Controller button, InputState inputState, int controllerId);
	void AddBindingToController(std::shared_ptr<BaseCommand> spCommand, XBoxController button, InputState inputState);
	void AddBindingToController(std::shared_ptr<BaseCommand> spCommand, XBoxController button, InputState inputState, int controllerId);
	void AddBindingToController(std::shared_ptr<BaseCommand> spCommand, SwitchController button, InputState inputState);
	void AddBindingToController(std::shared_ptr<BaseCommand> spCommand, SwitchController button, InputState inputState, int controllerId);

	template<typename myType>
	void RemoveBindingFromController(PS4Controller button);
	template<typename myType>
	void RemoveBindingFromController(PS4Controller button, int controllerId);
	template<typename myType>
	void RemoveBindingFromController(XBoxController button);
	template<typename myType>
	void RemoveBindingFromController(XBoxController button, int controllerId);
	template<typename myType>
	void RemoveBindingFromController(SwitchController button);
	template<typename myType>
	void RemoveBindingFromController(SwitchController button, int controllerId);

	void RemoveBindingFromController(PS4Controller button);
	void RemoveBindingFromController(PS4Controller button, int controllerId);
	void RemoveBindingFromController(XBoxController button);
	void RemoveBindingFromController(XBoxController button, int controllerId);
	void RemoveBindingFromController(SwitchController button);
	void RemoveBindingFromController(SwitchController button, int controllerId);

private:
	template<typename myType>
	void AddBindingToController(ApplicationController button, InputState inputState);
	template<typename myType>
	void AddBindingToController(ApplicationController button, InputState inputState, int controllerId);

	void AddBindingToController(std::shared_ptr<BaseCommand> spCommand, ApplicationController button, InputState inputState);
	void AddBindingToController(std::shared_ptr<BaseCommand> spCommand, ApplicationController button, InputState inputState, int controllerId);

	template<typename myType>
	void RemoveBindingFromController(ApplicationController button);
	template<typename myType>
	void RemoveBindingFromController(ApplicationController button, int controllerId);

	void RemoveBindingFromController(ApplicationController button);
	void RemoveBindingFromController(ApplicationController button, int controllerId);

	ApplicationController ConvertButton(PS4Controller button);
	ApplicationController ConvertButton(XBoxController button);
	ApplicationController ConvertButton(SwitchController button);
};

template<typename myType>
inline void InputManager::AddBindingToController(ApplicationController button, InputState inputState)
{
	for (Controller* pController : m_Controllers)
	{
		pController->AddConsoleCommand<myType>(button, inputState);
	}
}

template<typename myType>
inline void InputManager::AddBindingToController(ApplicationController button, InputState inputState, int controllerId)
{
	if (m_ControllerCount > controllerId && controllerId >= 0)
	{
		m_Controllers.at(controllerId)->AddConsoleCommand<myType>(button, inputState);
	}
	else
	{
		std::cout << "Invalid controller-id for binding." << std::endl;
	}
}

template<typename myType>
inline void InputManager::RemoveBindingFromController(ApplicationController button)
{
	for (Controller* pController : m_Controllers)
	{
		pController->RemoveConsoleCommand<myType>(button);
	}
}

template<typename myType>
inline void InputManager::RemoveBindingFromController(ApplicationController button, int controllerId)
{
	if (m_ControllerCount > controllerId && controllerId >= 0)
	{
		m_Controllers[controllerId]->RemoveConsoleCommand<myType>(button);
	}
	else
	{
		std::cout << "Invalid controller-id for binding." << std::endl;
	}
}

template<typename myType>
inline void InputManager::AddBindingToController(PS4Controller button, InputState inputState)
{
	AddBindingToController<myType>(ConvertButton(button), inputState);
}

template<typename myType>
inline void InputManager::AddBindingToController(PS4Controller button, InputState inputState, int controllerId)
{
	AddBindingToController<myType>(ConvertButton(button), inputState, controllerId);
}

template<typename myType>
inline void InputManager::AddBindingToController(XBoxController button, InputState inputState)
{
	AddBindingToController<myType>(ConvertButton(button), inputState);
}

template<typename myType>
inline void InputManager::AddBindingToController(XBoxController button, InputState inputState, int controllerId)
{
	AddBindingToController<myType>(ConvertButton(button), inputState, controllerId);
}

template<typename myType>
inline void InputManager::AddBindingToController(SwitchController button, InputState inputState)
{
	AddBindingToController<myType>(ConvertButton(button), inputState);
}

template<typename myType>
inline void InputManager::AddBindingToController(SwitchController button, InputState inputState, int controllerId)
{
	AddBindingToController<myType>(ConvertButton(button), inputState, controllerId);
}

template<typename myType>
inline void InputManager::RemoveBindingFromController(PS4Controller button)
{
	RemoveBindingFromController<myType>(ConvertButton(button));
}

template<typename myType>
inline void InputManager::RemoveBindingFromController(PS4Controller button, int controllerId)
{
	RemoveBindingFromController<myType>(ConvertButton(button), controllerId);
}

template<typename myType>
inline void InputManager::RemoveBindingFromController(XBoxController button)
{
	RemoveBindingFromController<myType>(ConvertButton(button));
}

template<typename myType>
inline void InputManager::RemoveBindingFromController(XBoxController button, int controllerId)
{
	RemoveBindingFromController<myType>(ConvertButton(button), controllerId);
}

template<typename myType>
inline void InputManager::RemoveBindingFromController(SwitchController button)
{
	RemoveBindingFromController<myType>(ConvertButton(button));
}

template<typename myType>
inline void InputManager::RemoveBindingFromController(SwitchController button, int controllerId)
{
	RemoveBindingFromController<myType>(ConvertButton(button), controllerId);
}