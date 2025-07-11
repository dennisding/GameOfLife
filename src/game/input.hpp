#pragma once

#include <memory>

class Win;

enum class KeyState
{
	None,
	Pressed,
	Released,
};

class Input
{
public:
	Input(Win* win);

	void pre_tick();

private:
	KeyState mouse_button_left_;

	Win* win_;
};

using InputPtr = std::shared_ptr<Input>;
