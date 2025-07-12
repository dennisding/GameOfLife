
#include "button.hpp"

#include <iostream>

Button::Button(int id, int x, int y, int width, int height)
	: id_(id), x_(x), y_(y), width_(width), height_(height), state_(ButtonState::None)
{

}

void Button::set_color(Color normal, Color click, Color hover)
{
	normal_ = normal;
	click_ = click;
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
	if (state_ == ButtonState::Pressed) {
		return;
	}

	if (in_range(x, y)) {
		state_ = ButtonState::Hover;
	}
	else {
		state_ = ButtonState::None;
	}
}

void Button::on_mouse_left_down(double x, double y)
{
	if (in_range(x, y)) {
		state_ = ButtonState::Pressed;
	}
}

bool Button::on_mouse_left_up(double x, double y)
{
	state_ = ButtonState::None;
	if (in_range(x, y)) {
		// trigger the click event
		if (on_click_event_) {
			on_click_event_();
		}
		return true;
	}

	return false;
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

	if (state_ == ButtonState::Pressed) {
		render_set->color_ = click_;
	}
	else if (state_ == ButtonState::Hover) {
		render_set->color_ = hover_;
	}
	else {
		render_set->color_ = normal_;
	}
	
	double xratio = 2.0f / win_width;
	double yratio = 2.0f / win_height;
	
	render_set->triangles_.add_rectangle(float(x_*xratio - 1.0), 
		float(y_ * yratio - 1.0), float(width_*xratio), float(height_*yratio));

	return render_set;
}

RenderSetPtr Button::get_icon_render_set()
{
	RenderSetPtr render_set = std::make_shared<RenderSet>();
	render_set->color_ = Color(0.95f, 0.50f, 0.50f);
	// Color icon_color = Color(0.95f, 0.50f, 0.50f);
	// hardcode now
	if (id_ == 1) {
		// step evolve
	}
	else if (id_ == 2) {

	}
	else {

	}

	return render_set;
}