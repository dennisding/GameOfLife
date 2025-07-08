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
		lifes_.emplace_back(Life(x, y));
	}

	// tick
	int evolve()
	{
		generation_ += 1;

		LifeVector new_lifes;

		for (int index = 0; index < lifes_.size(); ++index) {
			const Life& life = lifes_[index];
			check_neighbors(life, new_lifes);
		}

		// 
		new_lifes.swap(lifes_);

		return generation_;
	}

	void check_neighbors(const Life& life, LifeVector& new_lifes)
	{
		for (int x = -1; x <= 1; ++x) {
			for (int y = -1; y <= 1; ++y) {
				if (!((x == 0) && (y == 0))) { // skip self
					i64 new_x = life.x() + x;
					i64 new_y = life.y() + y;

					// the life exist
					// int count the neighbor
					int count = 0;
					bool is_alive = false;
					Life new_life(new_x, new_y);
					for (const auto& neighbor : lifes_) {
						if (neighbor.is_me(new_x, new_y)) {
							is_alive = true;
						}
						else if (new_life.is_neighbor(neighbor)) {
							count += 1;
						}
					}

					if ((count == 2) && is_alive) {
						// alive
						new_lifes.emplace_back(life);
					}
					else if (count == 3) {
						// new life
						new_lifes.emplace_back(Life(new_x, new_y));
					}
				}
			}
		}
	}

	bool head_death()
	{
		return lifes_.empty();
	}

private:
	LifeVector lifes_;
	int generation_;
};
