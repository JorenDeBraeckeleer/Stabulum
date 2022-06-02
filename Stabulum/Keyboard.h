#pragma once

class Keyboard
{
public:
	Keyboard() = default;

	~Keyboard() = default;
	Keyboard(const Keyboard& other) = delete;
	Keyboard(Keyboard&& other) = delete;
	Keyboard& operator=(const Keyboard& other) = delete;
	Keyboard& operator=(Keyboard&& other) = delete;

private:

};