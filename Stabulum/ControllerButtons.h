#pragma once

enum class ApplicationController
{
	DPadNorth,
	DPadSouth,
	DPadWest,
	DPadEast,
	SpecialButtonRight,
	SpecialButtonLeft,
	ThumbstickLeft,
	ThumbstickRight,
	BumperLeft,
	BumperRight,
	ButtonSouth,
	ButtonEast,
	ButtonWest,
	ButtonNorth,
};

enum class InputState
{
	Pressed = 1,
	Down = 2,
	Up = 3,
};

enum class PS4Controller
{
	DPadUp,
	DPadDown,
	DPadLeft,
	DPadRight,
	Options,
	Share,
	L3,
	R3,
	L1,
	R1,
	Cross,
	Circle,
	Square,
	Triangle,
};

enum class XBoxController
{
	DPadUp,
	DPadDown,
	DPadLeft,
	DPadRight,
	Start,
	Back,
	LeftStickButton,
	RightStickButton,
	LeftBumper,
	RightBumper,
	A,
	B,
	X,
	Y,
};

enum class SwitchController
{
	DirectionalUp,
	DirectionalDown,
	DirectionalLeft,
	DirectionalRight,
	Plus,
	Minus,
	LeftStickButton,
	RightStickButton,
	L,
	R,
	B,
	A,
	Y,
	X,
};