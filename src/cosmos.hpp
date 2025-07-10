#pragma once

#include "config.hpp"
#include "life.hpp"

#include <vector>

class Cosmos
{
public:
	class Iterator
	{
		LifeSet::iterator iter_;

	public:
		// inline
		inline Iterator(LifeSet::iterator iter) : iter_(iter) {}
		inline const Life* get_life() { return *iter_; }
		inline bool operator!=(const Iterator other) { return iter_ != other.iter_; }
		inline void operator++() { ++iter_; }
		inline Life* operator*() { return *iter_; }
	};
public:
	Cosmos();

	void add_life(i64 x, i64 y);
	int evolve(int step = 1);
	bool heat_death();
	bool operator==(const Cosmos& right) const;
	void reset();
	bool is_alive(Life life) const;

	const Iterator begin() const;
	const Iterator end() const;

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
