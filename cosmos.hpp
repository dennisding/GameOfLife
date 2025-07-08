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
			Life& life = lifes_[index];
			check_neighbors(life, new_lifes);
		}

		// 
		new_lifes.swap(lifes_);

		return generation_;
	}

	void check_neighbors(const Life& life, LifeVector& new_lifes)
	{
		// 遍历所有邻居
		for (int x = -1; x <= 1; ++x) {
			for (int y = -1; y <= 1; ++y) {
				// 排除自己
				if (!((x == 0) && (y == 0))) { // skip self
					Life neighbor(life.x() + x, life.y() + y);
					// 这里需要处理多次添加问题, 如果已经添加过了, 直接跳过
					bool exist = false;
					for (const auto& other : new_lifes) {
						if (other.is_me(neighbor)) {
							exist = true;
							break;
						}
					}
					if (exist) {
						continue;
					}

					int count = 0;
					bool is_alive = false;
					// 检查所有活着的对象, 看看是不是自己的邻居.
					for (const auto& other : lifes_) {
						if (other.is_me(life)) {
							is_alive = true;
						}
						else if (neighbor.is_neighbor(other)) {
							count += 1;
						}
					}

					if ((count == 2) && is_alive) {
						// alive
						new_lifes.emplace_back(neighbor);
					}
					else if (count == 3) {
						// new life
						new_lifes.emplace_back(neighbor);
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
