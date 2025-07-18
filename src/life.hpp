#pragma once

#include <cmath>
#include <set>

#include "config.hpp"
#include "allocator.hpp"

struct Life
{
	i64 x;
	i64 y;

public:
	explicit Life(const Life* life)
	{
		x = life->x;
		y = life->y;
	}

	Life(i64 in_x, i64 in_y) : x(in_x), y(in_y)
	{
	}

	inline bool is_me(const Life* life) const
	{
		return ((x == life->x) && (y == life->y));
	}

	inline bool is_neighbor(const Life* life) const
	{
		return (std::abs(x - life->x) <= 1) && (std::abs(y - life->y) <= 1);
	}

	inline bool operator==(const Life& right) const
	{
		return (x == right.x) && (y == right.y);
	}

	inline bool operator<(const Life& right) const
	{
		if (x < right.x) {
			return true;
		}
		if ((x == right.x) && (y < right.y)) {
			return true;
		}

		return false;
	}
};

struct CompareLife
{
	inline bool operator()(const Life* left, const Life* right) const
	{
		return *left < *right;
	}
};

using LifeSet = std::set<Life*, CompareLife>;
using LifeAllocator = Allocator<Life>;
