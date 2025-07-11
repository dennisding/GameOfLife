#pragma once

#include <memory>
#include <vector>

class GameSystem : std::enable_shared_from_this<GameSystem>
{
public:
	inline virtual void logic_pre_tick() {}
	inline virtual void logic_tick() {};
	inline virtual void logic_post_tick() {}

	inline virtual bool init() { return true; }
	inline virtual void render() {}
};

using GameSystemPtr = std::shared_ptr<GameSystem>;
using GameSystemVector = std::vector<GameSystemPtr>;