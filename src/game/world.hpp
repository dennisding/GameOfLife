
#pragma once

#include "cosmos.hpp"
#include "view_port.hpp"
#include "rectangle.hpp"
#include "wgpu/wcommand.hpp"

#include <chrono>
#include <memory>

class Game;

class World : std::enable_shared_from_this<World>
{
public:
	World(Game* game);
	~World();

	void init();
	void finit();
	
	void tick();
	void render(RenderPassCommandPtr render_pass);
	void render_self(TriangleSet& triangles);
	void render_lifes(TriangleSet& triangles);

	void evolve();
	void add_life(double x, double y);

	// process event
	bool on_mouse_drage(double x, double y);

	void auto_evolve();
	inline void pause_evolve() { auto_evolve_ = false; }

private:
	
private:
	Game* game_;
	Cosmos cosmos_;
	ViewportPtr viewport_;
	bool auto_evolve_;
	std::chrono::high_resolution_clock::time_point last_evolve_time_;
};

using WorldPtr = std::shared_ptr<World>;
