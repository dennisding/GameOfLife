#pragma once

#include "config.hpp"
#include "life.hpp"

#include <vector>

class Cosmos
{
public:
	Cosmos();

	void add_life(i64 x, i64 y);
	int evolve(int step = 1);
	bool heat_death();
	bool operator==(const Cosmos& right) const;
	void reset();
	bool is_alive(Life life) const;

private:
	void update_cosmos();
	void update_neighbors(const Life* life, LifeSet& updated, LifeSet& new_lifes);
	int count_neighbors(const Life* life);

private:
	LifeSet lifes_;
	LifeAllocator current_allocator;
	LifeAllocator new_life_allocator;
	int generation_;
};
