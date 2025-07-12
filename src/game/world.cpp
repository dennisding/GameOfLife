
#include "world.hpp"
#include "view_port.hpp"
#include "game.hpp"
#include "rectangle.hpp"

#include <iostream>

World::World(Game* game) : game_(game)
{
	auto_evolve_ = false;
}

World::~World()
{

}

void World::init()
{
	// make a 10x10 viewport
	viewport_ = std::make_shared<Viewport>(0, 0, 40);

	// cosmos_.add_life(0, -1);
	// cosmos_.add_life(0, 0);
	cosmos_.add_life(0, 1);
	cosmos_.add_life(1, 2);
	cosmos_.add_life(2, 0);
	cosmos_.add_life(2, 1);
	cosmos_.add_life(2, 2);
}

void World::finit()
{
	cosmos_.stop();
}

void World::tick()
{
	if (!auto_evolve_) {
		return;
	}

	auto duration = std::chrono::high_resolution_clock::now() - last_evolve_time_;
	// about 5 frame per second
	const double fps = 5;
	if (duration >= std::chrono::milliseconds(int(1.0/fps*1000)) ){
		// need evolve 
//		cosmos_.evolve();
		cosmos_.async_evolve();
		last_evolve_time_ = std::chrono::high_resolution_clock::now();
	}
}

void World::render(RenderPassCommandPtr render_pass)
{
	//render_world();
	//render_lifes();
}

void World::render_self(TriangleSet& triangles)
{
	WinPtr win = game_->get_win();
	double win_width = win->width();
	double win_height = win->height();

	double viewport_width = (float)viewport_->width();
	double xoffset = -viewport_width / 2;
	double yoffset = -viewport_width / 2;

	double xcell_pixel = (win_width / viewport_width)/win_width * 2.0;
	
	double xyratio = win_width / win_height;
	double ycell_pixel = xcell_pixel * xyratio;

	double xone_pixel = 2.0 / win_width;
	double yone_pixel = 2.0 / win_height;
	// 需要做视口变换
	for (int x = 0; x < viewport_width; ++x) {
		for (int y = 0; y < viewport_width; ++y) {
			triangles.add_rectangle(float((x + xoffset) * xcell_pixel), float((y + yoffset) * ycell_pixel), 
				float(xcell_pixel - xone_pixel), float(ycell_pixel - yone_pixel));
		}
	}

	// render the triangles
}

void World::render_lifes(TriangleSet& triangles)
{
	LifeSet lifes;
	i64 viewport_x = viewport_->x();
	i64 viewport_y = viewport_->y();
	int range = int(viewport_->width() / 2);

	cosmos_.capture(lifes, viewport_x, viewport_y, range);

	WinPtr win = game_->get_win();
	double win_width = win->width();
	double win_height = win->height();

	double viewport_width = (float)viewport_->width();
	double xoffset = -viewport_width / 2;
	double yoffset = -viewport_width / 2;

	double xcell_pixel = (win_width / viewport_width) / win_width * 2.0;

	double xyratio = win_width / win_height;
	double ycell_pixel = xcell_pixel * xyratio;

	double xone_pixel = 2.0 / win_width;
	double yone_pixel = 2.0 / win_height;

//	TriangleSet triangles;
	for (auto life : lifes) {
		// 
		i64 x = life->x - viewport_x + int(viewport_width/2);
		i64 y = life->y - viewport_y + int(viewport_width / 2);

		triangles.add_rectangle(float((x + xoffset) * xcell_pixel), float((y + yoffset) * ycell_pixel),
			float(xcell_pixel - xone_pixel), float(ycell_pixel - yone_pixel));
	}
}

void World::evolve()
{
	cosmos_.evolve();
}

void World::add_life(double x, double y)
{
	double win_width = game_->win_->width();
	double win_height = game_->win_->height();

	double cell_pixel = game_->win_->width() / (double)viewport_->width();
	double xoffset = x / cell_pixel;
	double yoffset = y / cell_pixel + (win_width - win_height)/2.0/cell_pixel;

	i64 life_x = i64(std::floor(viewport_->x() - viewport_->width() / 2.0 + xoffset));
	i64 life_y = i64(std::floor(viewport_->y() - viewport_->width() / 2.0 + yoffset));

	cosmos_.add_life(life_x, life_y);
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

void World::auto_evolve()
{
	auto_evolve_ = true;
	last_evolve_time_ = std::chrono::high_resolution_clock::now();
}
