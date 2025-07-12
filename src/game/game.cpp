
#include "game.hpp"

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

	gui_ = std::make_shared<Gui>();

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
	TriangleSet triangles;
	triangles.add_rectangle(-1, -1, 2, 2);
	render_triangles(triangles, 0.83, 0.92, 0.94, 1.0);

	render_world();
	render_lifes();
}

void Game::render_world()
{
	TriangleSet triangles;
	world_->render_self(triangles);

	render_triangles(triangles, 0.7, 0.7, 0.7, 1.0);
}

void Game::render_lifes()
{
	TriangleSet triangles;

	world_->render_lifes(triangles);

	render_triangles(triangles, 0.0, 0.4, 1.0, 1.0);
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

void Game::render_world(RenderPassCommandPtr render_pass)
{
	std::vector<float> vertexData = {
		// Define a first triangle:
		-0.5, -0.5,
		+0.5, -0.5,
		+0.0, +0.5,

		// Add a second triangle:
		-0.55f, -0.5,
		-0.05f, +0.5,
		-0.55f, +0.5
	};

	size_t size = vertexData.size() * sizeof(float);
	static auto buffer = device_->create_buffer(size);

	buffer->write(size, vertexData.data());
	render_pass->set_vertex_buffer(0, buffer);
	render_pass->draw(vertexData.size() / 2, 1);
}

void Game::on_mouse_drage(double x, double y)
{
	world_->on_mouse_drage(x, y);
}
