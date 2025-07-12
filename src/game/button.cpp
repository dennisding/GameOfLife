
#include "button.hpp"

#include <iostream>

Button::Button(int x, int y, int width, int height)
	: x_(x), y_(y), width_(width), height_(height), state_(ButtonState::None)
{

}

void Button::set_color(Color normal, Color hover)
{
	normal_ = normal;
	hover_ = hover;
}

bool Button::on_mouse_clicked(int x, int y)
{
	if (x < x_ || y_ < y) {
		return false;
	}

	if (x > (x_ + width_) || y > (y_ + height_)) {
		return false;
	}

	state_ = ButtonState::Pressed;
	return true;
}

void Button::on_mouse_move(double x, double y)
{
	if (in_range(x, y)) {
		state_ = ButtonState::Hover;
	}
	else {
		state_ = ButtonState::None;
	}
}

bool Button::in_range(double x, double y)
{
	if (x < x_ || y < y_) {
		return false;
	}
	if (x > (x_ + width_) || y > (y_ + height_)) {
		return false;
	}

	return true;
}

RenderSetPtr Button::get_render_set(int win_width, int win_height)
{
	RenderSetPtr render_set = std::make_shared<RenderSet>();

	if (state_ == ButtonState::Hover) {
		render_set->color_ = hover_;
	}
	else {
		render_set->color_ = normal_;
	}
	
	float xratio = 2.0f / win_width;
	float yratio = 2.0f / win_height;
	
	render_set->triangles_.add_rectangle(x_*xratio - 1.0, y_ * yratio - 1.0, width_*xratio, height_*yratio);

	return render_set;
}