
#include "gui.hpp"
#include "game.hpp"

Gui::Gui(Game* game) : game_(game)
{
	// Í¼°¸ 0.95, 0.50, 0.50
	// test button
	ButtonPtr button = std::make_shared<Button>(10, 10, 200, 123/2);

	// button 1
	button->set_color(Color(0.91f, 1.0f, 0.81f), Color(0.98f, 0.89f, 0.54f), Color(0.58f, 0.88f, 0.82f));
	buttons_.push_back(button);
	button->on_click_event_ = [game]() {
		game->world_->evolve();
		};

	// button 2
	button = std::make_shared<Button>(260, 10, 200, 123 / 2);
	button->set_color(Color(0.91f, 1.0f, 0.81f), Color(0.98f, 0.89f, 0.54f), Color(0.58f, 0.88f, 0.82f));
	buttons_.push_back(button);

	// button 3
	button = std::make_shared<Button>(510, 10, 200, 123 / 2);
	button->set_color(Color(0.91f, 1.0f, 0.81f), Color(0.98f, 0.89f, 0.54f), Color(0.58f, 0.88f, 0.82f));
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

void Gui::on_mouse_left_down(double x, double y)
{
	for (auto button : buttons_) {
		button->on_mouse_left_down(x, y);
	}
}

bool Gui::on_mouse_left_up(double x, double y)
{
	bool consume = false;
	for (auto button : buttons_) {
		consume = button->on_mouse_left_up(x, y);
		if (consume) {
			return true;
		}
	}
	return false;
}