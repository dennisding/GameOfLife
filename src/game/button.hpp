#pragma once

#include <vector>
#include <memory>

#include "color.hpp"
#include "render_set.hpp"

enum class ButtonState
{
	None,
	Pressed,
	Released,
	Hover,
	Unhover,
};

class Button : std::enable_shared_from_this<Button>
{
public:
	Button(int x, int y, int width, int height);

	void set_color(Color normal, Color click, Color hover);

	bool on_mouse_clicked(int x, int y);
	void on_mouse_move(double x, double y);
	void on_mouse_left_down(double x, double y);
	void on_mouse_left_up(double x, double y);

	RenderSetPtr get_render_set(int win_width, int win_height);

private:
	bool in_range(double x, double y);

private:
	int x_;
	int y_;
	int width_;
	int height_;
	Color normal_;
	Color click_;
	Color hover_;
	ButtonState state_;
};

using ButtonPtr = std::shared_ptr<Button>;
using ButtonVector = std::vector<ButtonPtr>;
