#pragma once

#include "config.hpp"
#include "life.hpp"
#include "thread_pool.hpp"

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
	int async_evolve(int step = 1);

	void stop();

	void capture(LifeSet& lifes, i64 x, i64 y, int range);
	bool heat_death();
	bool operator==(const Cosmos& right) const;
	void reset();
	bool is_alive(Life life) const;

	const Iterator begin() const;
	const Iterator end() const;

private:
	void update_cosmos();
	void async_update_cosmos();

	int count_neighbors(const Life* life);

	template <typename OwnershipHolderType>
	void update_neighbors(const Life* life, LifeSet& updated, 
		LifeSet& new_lifes, OwnershipHolderType& ownership_holder);

private:
	LifeSet lifes_;
	LifeAllocator current_allocator_;
	LifeAllocator new_life_allocator_;
	int generation_;
	ThreadPool thread_pool_;
};
