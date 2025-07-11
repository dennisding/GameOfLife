#pragma once

#include <memory>
#include <map>

#include "config.hpp"
#include "visual_life.hpp"
#include "cosmos.hpp"

class Viewport : std::enable_shared_from_this<Viewport>
{
public:
	Viewport(i64 x, i64 y, i64 width);
	~Viewport();

	void render_self();
	void render_lifes(Cosmos& cosmos);

	inline i64 width() { return width_; }
	inline i64 x() { return x_; }
	inline i64 y() { return y_; }

private:
	i64 x_;
	i64 y_;
	i64 width_;
	i64 height_;
};

using ViewportPtr = std::shared_ptr<Viewport>;
