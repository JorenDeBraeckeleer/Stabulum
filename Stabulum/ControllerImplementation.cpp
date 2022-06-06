#include "StabulumPCH.h"
#include "ControllerImplementation.h"

#pragma comment(lib, "xinput.lib")
#include <Xinput.h>

class ControllerImplementation::Implementation final
{
public:
	Implementation(int id)
		: m_ControllerIndex{ id }
	{
		ZeroMemory(&m_PreviousState, sizeof(XINPUT_STATE));
		ZeroMemory(&m_CurrentState, sizeof(XINPUT_STATE));
	}

	~Implementation() = default;
	Implementation(const Implementation& other) = delete;
	Implementation(Implementation&& other) = delete;
	Implementation& operator=(const Implementation& other) = delete;
	Implementation& operator=(Implementation&& other) = delete;

	bool Update()
	{
		std::swap(m_PreviousState, m_CurrentState);
		ZeroMemory(&m_CurrentState, sizeof(XINPUT_STATE));
		DWORD result{ XInputGetState(m_ControllerIndex, &m_CurrentState) };

		int buttonChanges = m_CurrentState.Gamepad.wButtons ^ m_PreviousState.Gamepad.wButtons;
		m_ButtonsPressed = buttonChanges & m_CurrentState.Gamepad.wButtons;
		m_ButtonsReleased = buttonChanges & (~m_CurrentState.Gamepad.wButtons);

		return !result;
	}

	bool IsPressed(unsigned int button) const
	{
		return m_CurrentState.Gamepad.wButtons & button;
	}

	bool IsDownThisFrame(unsigned int button) const
	{
		return m_ButtonsPressed & button;
	}

	bool IsUpThisFrame(unsigned int button) const
	{
		return m_ButtonsReleased & button;
	}

	unsigned int ConvertButton(ApplicationController button)
	{
		XInputController convertedButton{};

		switch (button)
		{
		case ApplicationController::DPadNorth:
			convertedButton = XInputController::DPadUp;
			break;
		case ApplicationController::DPadSouth:
			convertedButton = XInputController::DPadDown;
			break;
		case ApplicationController::DPadWest:
			convertedButton = XInputController::DPadLeft;
			break;
		case ApplicationController::DPadEast:
			convertedButton = XInputController::DPadRight;
			break;
		case ApplicationController::SpecialButtonRight:
			convertedButton = XInputController::Start;
			break;
		case ApplicationController::SpecialButtonLeft:
			convertedButton = XInputController::Back;
			break;
		case ApplicationController::ThumbstickLeft:
			convertedButton = XInputController::LeftThumb;
			break;
		case ApplicationController::ThumbstickRight:
			convertedButton = XInputController::RightThumb;
			break;
		case ApplicationController::BumperLeft:
			convertedButton = XInputController::LeftShoulder;
			break;
		case ApplicationController::BumperRight:
			convertedButton = XInputController::RightShoulder;
			break;
		case ApplicationController::ButtonSouth:
			convertedButton = XInputController::ButtonA;
			break;
		case ApplicationController::ButtonEast:
			convertedButton = XInputController::ButtonB;
			break;
		case ApplicationController::ButtonWest:
			convertedButton = XInputController::ButtonX;
			break;
		case ApplicationController::ButtonNorth:
			convertedButton = XInputController::ButtonY;
			break;
		default:
			break;
		}

		return static_cast<unsigned int>(convertedButton);
	}

	enum class XInputController
	{
		DPadUp = XINPUT_GAMEPAD_DPAD_UP,
		DPadDown = XINPUT_GAMEPAD_DPAD_DOWN,
		DPadLeft = XINPUT_GAMEPAD_DPAD_LEFT,
		DPadRight = XINPUT_GAMEPAD_DPAD_RIGHT,
		Start = XINPUT_GAMEPAD_START,
		Back = XINPUT_GAMEPAD_BACK,
		LeftThumb = XINPUT_GAMEPAD_LEFT_THUMB,
		RightThumb = XINPUT_GAMEPAD_RIGHT_THUMB,
		LeftShoulder = XINPUT_GAMEPAD_LEFT_SHOULDER,
		RightShoulder = XINPUT_GAMEPAD_RIGHT_SHOULDER,
		ButtonA = XINPUT_GAMEPAD_A,
		ButtonB = XINPUT_GAMEPAD_B,
		ButtonX = XINPUT_GAMEPAD_X,
		ButtonY = XINPUT_GAMEPAD_Y,
	};

private:
	XINPUT_STATE m_CurrentState{}, m_PreviousState{};
	WORD m_ButtonsPressed{}, m_ButtonsReleased{};
	int m_ControllerIndex{};
};

ControllerImplementation::ControllerImplementation(int id)
	: m_pImpl{ new Implementation{id} }
{
}

ControllerImplementation::~ControllerImplementation()
{
	delete m_pImpl;
	m_pImpl = nullptr;
}

bool ControllerImplementation::Update()
{
	return m_pImpl->Update();
}

bool ControllerImplementation::IsPressed(unsigned int button) const
{
	return m_pImpl->IsPressed(button);
}

bool ControllerImplementation::IsDownThisFrame(unsigned int button) const
{
	return m_pImpl->IsDownThisFrame(button);
}

bool ControllerImplementation::IsUpThisFrame(unsigned int button) const
{
	return m_pImpl->IsUpThisFrame(button);
}

unsigned int ControllerImplementation::ConvertButton(ApplicationController button)
{
	return m_pImpl->ConvertButton(button);
}