#include "StabulumPCH.h"
#include "Keyboard.h"

Keyboard::Keyboard()
	: m_pActiveState{ nullptr }
	, m_pPreviousState{ nullptr }
	, m_pKeyListLength{ new int{} }
{
	m_pActiveState = SDL_GetKeyboardState(m_pKeyListLength);
	m_pPreviousState = new UINT8[*m_pKeyListLength];
}

Keyboard::~Keyboard()
{
	delete m_pPreviousState;
	m_pPreviousState = nullptr;

	delete m_pKeyListLength;
	m_pKeyListLength = nullptr;

	for (auto& command : m_ConsoleCommands)
	{
		for (auto& action : command.pCommands)
		{
			delete action;
			action = nullptr;
		}
	}
}

void Keyboard::ProcessInput()
{
	std::memcpy(m_pPreviousState, m_pActiveState, *m_pKeyListLength);
}

bool Keyboard::IsPressed(unsigned int button) const
{
	if (m_pActiveState[button])
	{
		return true;
	}

	return false;
}

bool Keyboard::IsDownThisFrame(unsigned int button) const
{
	if (m_pActiveState[button] && !m_pPreviousState[button])
	{
		return true;
	}

	return false;
}

bool Keyboard::IsUpThisFrame(unsigned int button) const
{
	if (!m_pActiveState[button] && m_pPreviousState[button])
	{
		return true;
	}

	return false;
}

void Keyboard::AddConsoleCommand(std::shared_ptr<BaseCommand> spCommand, ApplicationKeyboard button, InputState inputState)
{
	SDLKeyboard convertedButton{ GetConvertedSDLButton(button) };

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

void Keyboard::RemoveConsoleCommand(ApplicationKeyboard button)
{
	for (auto& command : m_ConsoleCommands)
	{
		if (GetConvertedSDLButton(button) == command.Button)
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

unsigned int Keyboard::GetConvertedSDLButton(ApplicationKeyboard button) const
{
	SDL_Scancode convertedButton{};

	switch (button)
	{
	case ApplicationKeyboard::A:
		convertedButton = SDL_SCANCODE_A;
		break;
	case ApplicationKeyboard::B:
		convertedButton = SDL_SCANCODE_B;
		break;
	case ApplicationKeyboard::C:
		convertedButton = SDL_SCANCODE_C;
		break;
	case ApplicationKeyboard::D:
		convertedButton = SDL_SCANCODE_D;
		break;
	case ApplicationKeyboard::E:
		convertedButton = SDL_SCANCODE_E;
		break;
	case ApplicationKeyboard::F:
		convertedButton = SDL_SCANCODE_F;
		break;
	case ApplicationKeyboard::G:
		convertedButton = SDL_SCANCODE_G;
		break;
	case ApplicationKeyboard::H:
		convertedButton = SDL_SCANCODE_H;
		break;
	case ApplicationKeyboard::I:
		convertedButton = SDL_SCANCODE_I;
		break;
	case ApplicationKeyboard::J:
		convertedButton = SDL_SCANCODE_J;
		break;
	case ApplicationKeyboard::K:
		convertedButton = SDL_SCANCODE_K;
		break;
	case ApplicationKeyboard::L:
		convertedButton = SDL_SCANCODE_L;
		break;
	case ApplicationKeyboard::M:
		convertedButton = SDL_SCANCODE_M;
		break;
	case ApplicationKeyboard::N:
		convertedButton = SDL_SCANCODE_N;
		break;
	case ApplicationKeyboard::O:
		convertedButton = SDL_SCANCODE_O;
		break;
	case ApplicationKeyboard::P:
		convertedButton = SDL_SCANCODE_P;
		break;
	case ApplicationKeyboard::Q:
		convertedButton = SDL_SCANCODE_Q;
		break;
	case ApplicationKeyboard::R:
		convertedButton = SDL_SCANCODE_R;
		break;
	case ApplicationKeyboard::S:
		convertedButton = SDL_SCANCODE_S;
		break;
	case ApplicationKeyboard::T:
		convertedButton = SDL_SCANCODE_T;
		break;
	case ApplicationKeyboard::U:
		convertedButton = SDL_SCANCODE_U;
		break;
	case ApplicationKeyboard::V:
		convertedButton = SDL_SCANCODE_V;
		break;
	case ApplicationKeyboard::W:
		convertedButton = SDL_SCANCODE_W;
		break;
	case ApplicationKeyboard::X:
		convertedButton = SDL_SCANCODE_X;
		break;
	case ApplicationKeyboard::Y:
		convertedButton = SDL_SCANCODE_Y;
		break;
	case ApplicationKeyboard::Z:
		convertedButton = SDL_SCANCODE_Z;
		break;
	case ApplicationKeyboard::One:
		convertedButton = SDL_SCANCODE_1;
		break;
	case ApplicationKeyboard::Two:
		convertedButton = SDL_SCANCODE_2;
		break;
	case ApplicationKeyboard::Three:
		convertedButton = SDL_SCANCODE_3;
		break;
	case ApplicationKeyboard::Four:
		convertedButton = SDL_SCANCODE_4;
		break;
	case ApplicationKeyboard::Five:
		convertedButton = SDL_SCANCODE_5;
		break;
	case ApplicationKeyboard::Six:
		convertedButton = SDL_SCANCODE_6;
		break;
	case ApplicationKeyboard::Seven:
		convertedButton = SDL_SCANCODE_7;
		break;
	case ApplicationKeyboard::Eight:
		convertedButton = SDL_SCANCODE_8;
		break;
	case ApplicationKeyboard::Nine:
		convertedButton = SDL_SCANCODE_9;
		break;
	case ApplicationKeyboard::Zero:
		convertedButton = SDL_SCANCODE_0;
		break;
	case ApplicationKeyboard::Minus:
		convertedButton = SDL_SCANCODE_MINUS;
		break;
	case ApplicationKeyboard::Equals:
		convertedButton = SDL_SCANCODE_EQUALS;
		break;
	case ApplicationKeyboard::SquareBracketOpen:
		convertedButton = SDL_SCANCODE_RIGHTBRACKET;
		break;
	case ApplicationKeyboard::SquareBracketClose:
		convertedButton = SDL_SCANCODE_LEFTBRACKET;
		break;
	case ApplicationKeyboard::Semicolon:
		convertedButton = SDL_SCANCODE_SEMICOLON;
		break;
	case ApplicationKeyboard::Quote:
		convertedButton = SDL_SCANCODE_APOSTROPHE;
		break;
	case ApplicationKeyboard::Comma:
		convertedButton = SDL_SCANCODE_COMMA;
		break;
	case ApplicationKeyboard::Period:
		convertedButton = SDL_SCANCODE_PERIOD;
		break;
	case ApplicationKeyboard::SlashForward:
		convertedButton = SDL_SCANCODE_SLASH;
		break;
	case ApplicationKeyboard::SlashBackward:
		convertedButton = SDL_SCANCODE_BACKSLASH;
		break;
	case ApplicationKeyboard::F1:
		convertedButton = SDL_SCANCODE_F1;
		break;
	case ApplicationKeyboard::F2:
		convertedButton = SDL_SCANCODE_F2;
		break;
	case ApplicationKeyboard::F3:
		convertedButton = SDL_SCANCODE_F3;
		break;
	case ApplicationKeyboard::F4:
		convertedButton = SDL_SCANCODE_F4;
		break;
	case ApplicationKeyboard::F5:
		convertedButton = SDL_SCANCODE_F5;
		break;
	case ApplicationKeyboard::F6:
		convertedButton = SDL_SCANCODE_F6;
		break;
	case ApplicationKeyboard::F7:
		convertedButton = SDL_SCANCODE_F7;
		break;
	case ApplicationKeyboard::F8:
		convertedButton = SDL_SCANCODE_F8;
		break;
	case ApplicationKeyboard::F9:
		convertedButton = SDL_SCANCODE_F9;
		break;
	case ApplicationKeyboard::F10:
		convertedButton = SDL_SCANCODE_F10;
		break;
	case ApplicationKeyboard::F11:
		convertedButton = SDL_SCANCODE_F11;
		break;
	case ApplicationKeyboard::F12:
		convertedButton = SDL_SCANCODE_F12;
		break;
	case ApplicationKeyboard::NumPad_NumLock:
		convertedButton = SDL_SCANCODE_NUMLOCKCLEAR;
		break;
	case ApplicationKeyboard::NumPad_Divide:
		convertedButton = SDL_SCANCODE_KP_DIVIDE;
		break;
	case ApplicationKeyboard::NumPad_Multiply:
		convertedButton = SDL_SCANCODE_KP_MULTIPLY;
		break;
	case ApplicationKeyboard::NumPad_Minus:
		convertedButton = SDL_SCANCODE_KP_MINUS;
		break;
	case ApplicationKeyboard::NumPad_Plus:
		convertedButton = SDL_SCANCODE_KP_PLUS;
		break;
	case ApplicationKeyboard::NumPad_Enter:
		convertedButton = SDL_SCANCODE_KP_ENTER;
		break;
	case ApplicationKeyboard::NumPad_Comma:
		convertedButton = SDL_SCANCODE_KP_COMMA;
		break;
	case ApplicationKeyboard::NumPad_0:
		convertedButton = SDL_SCANCODE_KP_0;
		break;
	case ApplicationKeyboard::NumPad_1:
		convertedButton = SDL_SCANCODE_KP_1;
		break;
	case ApplicationKeyboard::NumPad_2:
		convertedButton = SDL_SCANCODE_KP_2;
		break;
	case ApplicationKeyboard::NumPad_3:
		convertedButton = SDL_SCANCODE_KP_3;
		break;
	case ApplicationKeyboard::NumPad_4:
		convertedButton = SDL_SCANCODE_KP_4;
		break;
	case ApplicationKeyboard::NumPad_5:
		convertedButton = SDL_SCANCODE_KP_5;
		break;
	case ApplicationKeyboard::NumPad_6:
		convertedButton = SDL_SCANCODE_KP_6;
		break;
	case ApplicationKeyboard::NumPad_7:
		convertedButton = SDL_SCANCODE_KP_7;
		break;
	case ApplicationKeyboard::NumPad_8:
		convertedButton = SDL_SCANCODE_KP_8;
		break;
	case ApplicationKeyboard::NumPad_9:
		convertedButton = SDL_SCANCODE_KP_9;
		break;
	case ApplicationKeyboard::Escape:
		convertedButton = SDL_SCANCODE_ESCAPE;
		break;
	case ApplicationKeyboard::Grave:
		convertedButton = SDL_SCANCODE_GRAVE;
		break;
	case ApplicationKeyboard::Tab:
		convertedButton = SDL_SCANCODE_TAB;
		break;
	case ApplicationKeyboard::CapsLock:
		convertedButton = SDL_SCANCODE_CAPSLOCK;
		break;
	case ApplicationKeyboard::ShiftLeft:
		convertedButton = SDL_SCANCODE_LSHIFT;
		break;
	case ApplicationKeyboard::ShiftRight:
		convertedButton = SDL_SCANCODE_RSHIFT;
		break;
	case ApplicationKeyboard::ControlLeft:
		convertedButton = SDL_SCANCODE_LCTRL;
		break;
	case ApplicationKeyboard::ControlRight:
		convertedButton = SDL_SCANCODE_RCTRL;
		break;
	case ApplicationKeyboard::WindowsLeft:
		convertedButton = SDL_SCANCODE_LGUI;
		break;
	case ApplicationKeyboard::WindowsRight:
		convertedButton = SDL_SCANCODE_RGUI;
		break;
	case ApplicationKeyboard::AltLeft:
		convertedButton = SDL_SCANCODE_LALT;
		break;
	case ApplicationKeyboard::AltRight:
		convertedButton = SDL_SCANCODE_RALT;
		break;
	case ApplicationKeyboard::Space:
		convertedButton = SDL_SCANCODE_SPACE;
		break;
	case ApplicationKeyboard::Enter:
		convertedButton = SDL_SCANCODE_RETURN;
		break;
	case ApplicationKeyboard::Backspace:
		convertedButton = SDL_SCANCODE_BACKSPACE;
		break;
	case ApplicationKeyboard::ArrowUp:
		convertedButton = SDL_SCANCODE_UP;
		break;
	case ApplicationKeyboard::ArrowDown:
		convertedButton = SDL_SCANCODE_DOWN;
		break;
	case ApplicationKeyboard::ArrowLeft:
		convertedButton = SDL_SCANCODE_LEFT;
		break;
	case ApplicationKeyboard::ArrowRight:
		convertedButton = SDL_SCANCODE_RIGHT;
		break;
	case ApplicationKeyboard::PrintScreen:
		convertedButton = SDL_SCANCODE_PRINTSCREEN;
		break;
	case ApplicationKeyboard::ScrollLock:
		convertedButton = SDL_SCANCODE_SCROLLLOCK;
		break;
	case ApplicationKeyboard::Pause:
		convertedButton = SDL_SCANCODE_PAUSE;
		break;
	case ApplicationKeyboard::Insert:
		convertedButton = SDL_SCANCODE_INSERT;
		break;
	case ApplicationKeyboard::Home:
		convertedButton = SDL_SCANCODE_HOME;
		break;
	case ApplicationKeyboard::PageUp:
		convertedButton = SDL_SCANCODE_PAGEUP;
		break;
	case ApplicationKeyboard::Delete:
		convertedButton = SDL_SCANCODE_DELETE;
		break;
	case ApplicationKeyboard::End:
		convertedButton = SDL_SCANCODE_END;
		break;
	case ApplicationKeyboard::PageDown:
		convertedButton = SDL_SCANCODE_PAGEDOWN;
		break;
	default:
		break;
	}
	
	return convertedButton;
}