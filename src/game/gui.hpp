#pragma once

#include <memory>

#include "button.hpp"
#include "render_set.hpp"

class Game;

class Gui : std::enable_shared_from_this<Gui>
{
public:
	Gui(Game* game);

	void tick();

	bool on_mouse_click(int x, int y);
	void on_mouse_move(double x, double y);
	void on_mouse_left_down(double x, double y);
	void on_mouse_left_up(double x, double y);

	void render(RenderSetVector& render_sets, int win_width, int win_height);

private:
	Game* game_;
	ButtonVector buttons_;
};

using GuiPtr = std::shared_ptr<Gui>;
