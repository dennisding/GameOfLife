#pragma once

#include "win.hpp"
#include "world.hpp"
#include "gui.hpp"
#include "time_controller.hpp"
#include "rectangle.hpp"

#include "wgpu/wadapter.hpp"
#include "wgpu/wrender_pass.hpp"
#include "wgpu/wcommand_buffer.hpp"

#include <chrono>

class Game
{
public:
	Game();
	~Game();

	bool init();
	void run();
	void pre_tick();
	bool tick();
	void post_tick();
	void finit();

	inline WinPtr get_win() { return win_; }

private:
	void tick_logic();
	void render();
	void render_world();
	void render_lifes();
	void render_world(RenderPassCommandPtr render_pass);
	void render_triangles(TriangleSet& triangles, float r = 0., float g = 0., float b = 0.);

private:
	WinPtr win_;
	AdapterPtr adapter_;
	DevicePtr device_;

	// logic
	WorldPtr world_;
	GuiPtr gui_;
	TimeController time_controller_;
};