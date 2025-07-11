
#include "input.hpp"
#include "win.hpp"
#include "game.hpp"


Input::Input(Win* win) : win_(win)
{
	mouse_button_left_ = KeyState::None;
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
}