#pragma once

#include "config.hpp"
#include "life.hpp"

#include <vector>

class Cosmos
{
public:
	Cosmos() : generation_(0)
	{
	}

	void add_life(i64 x, i64 y)
	{
		Life* life = current_allocator.allocate(x, y);

		lifes_.insert(life);
	}

	int evolve(int step = 1)
	{
		for (int index = 0; index < step; ++index) {
			generation_ += 1;

			update_cosmos();
		}
		return generation_;
	}

	void update_cosmos()
	{
		LifeSet updated;
		LifeSet new_lifes;

		for (auto& life : lifes_) {
			update_neighbors(life, updated, new_lifes);
		}

		lifes_.swap(new_lifes);
		current_allocator.swap(new_life_allocator);
		new_life_allocator.reset();
	}

	void update_neighbors(const Life* life, LifeSet& updated, LifeSet& new_lifes)
	{
		for (int x = -1; x <= 1; ++x) {
			for (int y = -1; y <= 1; ++y) {
				if ((x != 0) || (y != 0)) { // ignore self
					i64 neighbor_x = life->x + x;
					i64 neighbor_y = life->y + y;
					
					Life neighbor(neighbor_x, neighbor_y);
					// already updated, continue
					if (updated.find(&neighbor) != updated.end()) {
						continue;
					}

					// updated
					updated.insert(current_allocator.allocate(&neighbor));

					int count = count_neighbors(&neighbor);
					if (count == 3) {
						// new life 
						new_lifes.insert(new_life_allocator.allocate(&neighbor));
					}
					else if ((count == 2) && (lifes_.find(&neighbor) != lifes_.end())) {
						// alive
						new_lifes.insert(new_life_allocator.allocate(&neighbor));
					}
				}
			}
		}
	}

	// check the neighbor in the following order
	// x00      0x0      00x
	// x00  ->  000  ->  00x
	// x00      0x0      00x
	int count_neighbors(const Life* life)
	{
		int count = 0;

		for (int index = -1; index < 2; ++index) {
			Life bounder_life(life->x + index, life->y - 1);
			
			int step = 0;
			auto life_iter = lifes_.lower_bound(&bounder_life);
			while ((step < 3) && (life_iter != lifes_.end())) {
				if ((*life_iter)->x != bounder_life.x) { // not in the same colum, next iter
					break;
				}
				if ((*life_iter)->is_me(life)) { // it's me, do nothing

				}
				else if ((*life_iter)->is_neighbor(life)) {
					++count;
				}

				// next iter
				++step;
				++life_iter;
			}
		}

		return count;
	}

	bool heat_death()
	{
		return lifes_.empty();
	}

	bool operator==(const Cosmos& right) const
	{
		if (lifes_.size() != right.lifes_.size()) {
			return false;
		}
		auto iter = lifes_.begin();
		auto right_iter = right.lifes_.begin();
		while (iter != lifes_.end()) {
			if (!(**iter == **right_iter)) {
				return false;
			}
			// equal size
			++iter;
			++right_iter;
		}

		return true;
	}

	void reset()
	{
		lifes_.clear();
		current_allocator.reset();
		new_life_allocator.reset();
		generation_ = 0;
	}

	bool is_alive(Life life) const
	{
		return lifes_.find(&life) != lifes_.end();
	}

private:
	LifeSet lifes_;
	LifeAllocator current_allocator;
	LifeAllocator new_life_allocator;
	int generation_;
};
