
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

	win_ = std::make_shared<Win>();
	if (!win_->init(640, 480, "Game Of Life")) {
		return false;
	}

	device_ = adapter_->get_device();
	device_->config_surface(win_->window_);

	return true;
}

void Game::pre_tick()
{
	device_->pre_tick();
}

bool Game::tick()
{
	if (!win_->tick()) {
		return false;
	}

	pre_tick();

	device_->tick();

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
	auto render_pass = device_->create_render_pass_command();

	render_pass->begin(device_->get_surface_texture());
	render_pass->end();
	render_pass->submit();
}
