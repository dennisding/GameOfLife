#pragma once

#include "win.hpp"
#include "world.hpp"
#include "gui.hpp"
#include "geometry.hpp"

#include "wgpu/wadapter.hpp"
#include "wgpu/wcommand.hpp"
#include "wgpu/wpipe_line_layout.hpp"
#include "wgpu/wbind_group.hpp"

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
	void render_gui();

//	void render_world(RenderPassCommandPtr render_pass);
	void render_triangles(TriangleSet& triangles, float r = 0.5, float g = 0.5, float b = 0.5, float a = 1.);

public:
	// keyboard event
	void on_mouse_drage(double x, double y);
	void on_mouse_move(double x, double y);
	void on_mouse_left_down(double x, double y);
	bool on_mouse_left_up(double x, double y);

public:
	// use internal
	WinPtr win_;
	AdapterPtr adapter_;
	DevicePtr device_;

	// logic
	WorldPtr world_;
	GuiPtr gui_;
	
	PipeLineLayoutPtr pipe_line_layout_;
	BindGroupPtr bind_group_;
};