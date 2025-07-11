#pragma once

#include "win.hpp"
#include "wgpu/wadapter.hpp"
#include "wgpu/wrender_pass.hpp"
#include "wgpu/wcommand_buffer.hpp"

class Game
{
public:
	Game();
	~Game();

	bool init();
	void pre_tick();
	bool tick();
	void post_tick();
	void finit();

private:
	void tick_logic();
	void render();
	void render_world(RenderPassCommandPtr render_pass);

private:
	WinPtr win_;
	AdapterPtr adapter_;
	DevicePtr device_;
};