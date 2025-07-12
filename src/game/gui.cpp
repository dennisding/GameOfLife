
#include "gui.hpp"
#include "game.hpp"

Gui::Gui(Game* game) : game_(game)
{
	ButtonPtr button = std::make_shared<Button>(10, 10, 200, 123/2);

	button->set_color(Color(0.1f, 0.1f, 0.1f), Color(0.8f, 0.8f, 0.8f));
	buttons_.push_back(button);
}

void Gui::tick()
{

}

void Gui::render(RenderSetVector& render_sets, int win_width, int win_height)
{
	for (auto button : buttons_) {
		render_sets.push_back(button->get_render_set(win_width, win_height));
	}
}

bool Gui::on_mouse_click(int x, int y)
{
	bool consume = false;
	for (auto button : buttons_) {
		consume = consume || button->on_mouse_clicked(x, y);
	}

	return consume;
}

void Gui::on_mouse_move(double x, double y)
{
	for (auto button : buttons_) {
		button->on_mouse_move(x, y);
	}
}