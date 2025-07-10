
#include "game.hpp"

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
	if (!win_->init(1024, 768, "Game Of Life")) {
		return false;
	}

	return true;
}

bool Game::tick()
{
	return win_->tick();
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