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

	// 如果想要更高效一点, 可以对updated 和 new_lifes的ownership做区分, 
	// 不过应该没有很大的必要.
	template <typename OwnershipHolderType>
	void update_neighbors(const Life* life, LifeSet& updated, LifeSet& new_lifes, 
				OwnershipHolderType& ownership_holder)
	{
		for (int x = -1; x <= 1; ++x) {
			for (int y = -1; y <= 1; ++y) {
				i64 neighbor_x = life->x + x;
				i64 neighbor_y = life->y + y;
		
				Life neighbor(neighbor_x, neighbor_y);
				// already updated, continue
				ownership_holder.take();
					
				if (updated.find(&neighbor) != updated.end()) {
					ownership_holder.release();
					continue;
				}
		
				// updated
				updated.insert(current_allocator_.allocate(&neighbor));

				ownership_holder.release();
		
				int count = count_neighbors(&neighbor);
				if (count == 3) {
					// new life 
					ownership_holder.take();
					new_lifes.insert(new_life_allocator_.allocate(&neighbor));
					ownership_holder.release();
				}
				else if ((count == 2) && (lifes_.find(&neighbor) != lifes_.end())) {
					// alive
					ownership_holder.take();
					new_lifes.insert(new_life_allocator_.allocate(&neighbor));
					ownership_holder.release();
				}
			}
		}
	}

private:
	LifeSet lifes_;
	LifeAllocator current_allocator_;
	LifeAllocator new_life_allocator_;
	int generation_;
	ThreadPool thread_pool_;
};
