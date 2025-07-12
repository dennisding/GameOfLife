
#pragma once

#include "cosmos.hpp"
#include "view_port.hpp"
#include "rectangle.hpp"
#include "wgpu/wcommand_buffer.hpp"


#include <memory>

class Game;

class World : std::enable_shared_from_this<World>
{
public:
	World(Game* game);
	~World();

	void init();
	
	void tick();
	void render(RenderPassCommandPtr render_pass);
	void render_self(TriangleSet& triangles);
	void render_lifes(TriangleSet& triangles);

	void evolve();
	void add_life(double x, double y);

	// process event
	bool on_mouse_drage(double x, double y);

private:
	
private:
	Game* game_;
	Cosmos cosmos_;
	ViewportPtr viewport_;
};

using WorldPtr = std::shared_ptr<World>;
