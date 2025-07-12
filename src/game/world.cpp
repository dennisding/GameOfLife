
#include "world.hpp"
#include "view_port.hpp"
#include "game.hpp"
#include "rectangle.hpp"

#include <iostream>

World::World(Game* game) : game_(game)
{
}

World::~World()
{

}

void World::init()
{
	// make a 10x10 viewport
	viewport_ = std::make_shared<Viewport>(0, 0, 40);

	cosmos_.add_life(0, 1);
	cosmos_.add_life(1, 2);
	cosmos_.add_life(2, 0);
	cosmos_.add_life(2, 1);
	cosmos_.add_life(2, 2);
}

void World::tick()
{
//	std::count << "world tick" << std::end;

//	cosmos_.evolve();
}

void World::render(RenderPassCommandPtr render_pass)
{
	//render_world();
	//render_lifes();
}

void World::render_self(TriangleSet& triangles)
{
	WinPtr win = game_->get_win();
	float win_width = (float)win->width();
	float win_height = (float)win->height();

	float viewport_width = (float)viewport_->width();
	float xoffset = -viewport_width / 2;
	float yoffset = -viewport_width / 2;

	float xcell_pixel = (win_width / viewport_width)/win_width * 2.0;
	
	float xyratio = win_width / win_height;
	float ycell_pixel = xcell_pixel * xyratio;
	
	float xone_pixel = 2.0 / win_width;
	float yone_pixel = 2.0 / win_height;
	// 需要做视口变换
	for (int x = 0; x < viewport_width; ++x) {
		for (int y = 0; y < viewport_width; ++y) {
			triangles.add_rectangle((x + xoffset) * xcell_pixel, (y + yoffset) * ycell_pixel, 
				xcell_pixel - xone_pixel, ycell_pixel - yone_pixel);
		}
	}

	// render the triangles
}

void World::render_lifes(TriangleSet& triangles)
{
	LifeSet lifes;
	i64 viewport_x = viewport_->x();
	i64 viewport_y = viewport_->y();
	int range = viewport_->width() / 2;

	cosmos_.capture(lifes, viewport_x, viewport_y, range);

	WinPtr win = game_->get_win();
	float win_width = win->width();
	float win_height = win->height();

	float viewport_width = viewport_->width();
	float xoffset = -viewport_width / 2;
	float yoffset = -viewport_width / 2;

	float xcell_pixel = (win_width / viewport_width) / win_width * 2.0;

	float xyratio = win_width / win_height;
	float ycell_pixel = xcell_pixel * xyratio;

	float xone_pixel = 2.0 / win_width;
	float yone_pixel = 2.0 / win_height;

//	TriangleSet triangles;
	for (auto life : lifes) {
		// 
		i64 x = life->x - viewport_x + viewport_width/2;
		i64 y = life->y - viewport_y + viewport_width / 2;

		triangles.add_rectangle((x + xoffset) * xcell_pixel, (y + yoffset) * ycell_pixel,
			xcell_pixel - xone_pixel, ycell_pixel - yone_pixel);
	}
}

void World::evolve()
{
	cosmos_.evolve();
}

bool World::on_mouse_drage(double x, double y)
{
	double offsetx = x / game_->win_->width() * viewport_->width() / 1;
	double offsety = y / game_->win_->height() * viewport_->width() / 1;
	if (int(offsetx) == 0 && int(offsety) == 0) {
		return false;
	}

	i64 center_x = viewport_->x() + (int)offsetx;
	i64 center_y = viewport_->y() - (int)offsety;
	viewport_->set_center(center_x, center_y);

	return true;
}
