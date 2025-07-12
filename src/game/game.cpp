
#include "game.hpp"
#include "render_set.hpp"

#include <chrono>
#include <thread>

Game::Game()
{
}

bool Game::init()
{
	glfwInit();

	// wgpu adapter
	adapter_ = std::make_shared<Adapter>();
	if (!adapter_->init()) {
		return false;
	}

	win_ = std::make_shared<Win>(this);
	if (!win_->init(1024, 768, "Game Of Life")) {
		return false;
	}

	device_ = adapter_->get_device();
	device_->config_surface(win_->window_);

	// create device relative
	pipe_line_layout_ = device_->create_pipe_line_layout();
	bind_group_ = pipe_line_layout_->create_bind_group(sizeof(float)* 4); // to hold r, g, b, a

	std::vector<float> color = {0.5, 0.5, 0.5, 1.0};
	bind_group_->buffer_->write(sizeof(float) * color.size(), color.data());

	world_ = std::make_shared<World>(this);
	world_->init();

	gui_ = std::make_shared<Gui>(this);

	return true;
}

void Game::run()
{
	// frame control
}

void Game::pre_tick()
{
	device_->pre_tick();
	win_->pre_tick();
}

bool Game::tick()
{
	if (!win_->tick()) {
		return false;
	}

	pre_tick();

	device_->tick();
	world_->tick();

//	tick_logic();
	render();

	post_tick();

	std::this_thread::sleep_for(std::chrono::milliseconds(1));
	return true;
}

void Game::post_tick()
{
	device_->post_tick();
}

void Game::finit()
{
	win_->finit();
	win_ = nullptr;

	world_->finit();

	adapter_ = nullptr;
}

Game::~Game()
{
}

void Game::tick_logic()
{

}

void Game::render()
{
	// clear the surface
	TriangleSet triangles;
	triangles.add_rectangle(-1, -1, 2, 2);
	render_triangles(triangles, 0.83f, 0.92f, 0.94f, 1.0f);

	render_world();
	render_lifes();
	render_gui();
}

void Game::render_world()
{
	TriangleSet triangles;
	world_->render_self(triangles);

	render_triangles(triangles, 0.7f, 0.7f, 0.7f, 1.0f);
}

void Game::render_lifes()
{
	TriangleSet triangles;

	world_->render_lifes(triangles);

	render_triangles(triangles, 0.0f, 0.4f, 1.0f, 1.0f);
}

void Game::render_gui()
{
	RenderSetVector render_sets;
	
	gui_->render(render_sets, win_->width(), win_->height());

	for (auto render_set : render_sets) {
		auto color = render_set->color_;
		render_triangles(render_set->triangles_, color.x, color.y, color.z, 1.0);
	}
}

void Game::render_triangles(TriangleSet& triangles, float r, float g, float b, float a)
{
	if (triangles.vertexs_.empty()) {
		return;
	}
	// update the bind group
	std::vector<float> color = { r, g, b, a };
	bind_group_->buffer_->write(sizeof(float)*color.size(), color.data());

	auto pipe_line = device_->create_render_pipe_line(pipe_line_layout_);

	auto render_pass = device_->create_render_pass_command();
	render_pass->begin(device_->get_surface_texture());

	render_pass->set_pipe_line(pipe_line);
	render_pass->set_bind_group(0, bind_group_);

	// do the triangles
	size_t size = triangles.vertexs_.size() * sizeof(float);
	auto buffer = device_->create_buffer(size);
	buffer->write(size, triangles.vertexs_.data());

	render_pass->set_vertex_buffer(0, buffer);
	render_pass->draw(triangles.vertexs_.size() / 2, 1);

	render_pass->end();
	render_pass->submit();
}

void Game::on_mouse_drage(double x, double y)
{
	world_->on_mouse_drage(x, y);
}

void Game::on_mouse_left_down(double x, double y)
{
	gui_->on_mouse_left_down(x, y);
}

bool Game::on_mouse_left_up(double x, double y)
{
	bool consume = gui_->on_mouse_left_up(x, y);
	if (!consume) {
		world_->add_life(x, y);
	}
	return consume;
}

void Game::on_mouse_move(double x, double y)
{
	gui_->on_mouse_move(x, y);
}
