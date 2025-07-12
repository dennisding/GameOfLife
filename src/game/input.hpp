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
	KeyState mouse_button_right_;
	double cursor_x_;
	double cursor_y_;
	double scroll_x_;
	double scroll_y_;

	Win* win_;
};

using InputPtr = std::shared_ptr<Input>;
