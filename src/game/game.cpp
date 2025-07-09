
#include "game.hpp"

Game::Game()
{
}

bool Game::init()
{
	glfwInit();

	// wgpu adapter
	adapter_ = std::make_shared<Adapter>();
	adapter_->init();

	win_ = std::make_shared<Win>();
	win_->init(1024, 768, "Game Of Life");

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