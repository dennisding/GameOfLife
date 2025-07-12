
#include "input.hpp"
#include "win.hpp"
#include "game.hpp"


Input::Input(Win* win) : win_(win), cursor_x_(0), cursor_y_(0)
{
	mouse_button_left_ = KeyState::None;

	glfwGetCursorPos(win_->window_, &cursor_x_, &cursor_y_);
}

void Input::pre_tick()
{
	int state = glfwGetMouseButton(win_->window_, GLFW_MOUSE_BUTTON_LEFT);
	if (state == GLFW_PRESS) {
		mouse_button_left_ = KeyState::Pressed;
	}
	else if (mouse_button_left_ == KeyState::Pressed && state == GLFW_RELEASE) {
		// trigger a event
		win_->game_->world_->evolve();
		mouse_button_left_ = KeyState::Released;
	}

	// process the right button
	state = glfwGetMouseButton(win_->window_, GLFW_MOUSE_BUTTON_RIGHT);
	if (state == GLFW_PRESS) {
		if (mouse_button_right_ == KeyState::Released) {
			glfwGetCursorPos(win_->window_, &cursor_x_, &cursor_y_);
		}
		else {
			double x, y;
			glfwGetCursorPos(win_->window_, &x, &y);
			bool consume = win_->game_->world_->on_mouse_drage( x - cursor_x_, y - cursor_y_);
			if (consume) {
				cursor_x_ = x;
				cursor_y_ = y;
			}
		}
		
		mouse_button_right_ = KeyState::Pressed;
	}
	else {
		mouse_button_right_ = KeyState::Released;
	}
}