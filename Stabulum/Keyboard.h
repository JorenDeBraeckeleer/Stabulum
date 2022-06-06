#pragma once

#include "ButtonMapping.h"

class Keyboard final
{
public:
	Keyboard();
	~Keyboard();

	Keyboard(const Keyboard& other) = delete;
	Keyboard(Keyboard&& other) = delete;
	Keyboard& operator=(const Keyboard& other) = delete;
	Keyboard& operator=(Keyboard&& other) = delete;

	std::vector<InputCommand>* GetConsoleCommands() { return &m_ConsoleCommands; }

	void ProcessInput();

	using SDLKeyboard = unsigned int;

	bool IsPressed(SDLKeyboard button) const;
	bool IsDownThisFrame(SDLKeyboard button) const;
	bool IsUpThisFrame(SDLKeyboard button) const;

	SDLKeyboard GetConvertedSDLButton(ApplicationKeyboard button) const;

	template<typename myType>
	void AddConsoleCommand(ApplicationKeyboard button, InputState inputState);

	void AddConsoleCommand(std::shared_ptr<BaseCommand> spCommand, ApplicationKeyboard button, InputState inputState);

	template<typename myType>
	void RemoveConsoleCommand(ApplicationKeyboard button);

	void RemoveConsoleCommand(ApplicationKeyboard button);

private:
	const Uint8* m_pActiveState;
	Uint8* m_pPreviousState;
	int* m_pKeyListLength;

	std::vector<InputCommand> m_ConsoleCommands{};
};

template<typename myType>
inline void Keyboard::AddConsoleCommand(ApplicationKeyboard button, InputState inputState)
{
	SDLKeyboard convertedButton{ GetConvertedSDLButton(button) };

	for (auto& command : m_ConsoleCommands)
	{
		if (convertedButton == command.Button)
		{
			command.pCommands.push_back(new myType());
			return;
		}
	}

	InputCommand controllerCommand{};
	controllerCommand.Button = convertedButton;
	controllerCommand.InputState = inputState;
	controllerCommand.pCommands.push_back(new myType());
	m_ConsoleCommands.push_back(controllerCommand);
}

template<typename myType>
inline void Keyboard::RemoveConsoleCommand(ApplicationKeyboard button)
{
	for (auto& command : m_ConsoleCommands)
	{
		if (GetConvertedSDLButton(button) == command.Button)
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