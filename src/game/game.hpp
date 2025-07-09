#pragma once

#include "win.hpp"
#include "wgpu/wadapter.hpp"

class Game
{
public:
	Game();
	~Game();

	bool init();
	bool tick();
	void finit();

private:
	WinPtr win_;
	AdapterPtr adapter_;
};