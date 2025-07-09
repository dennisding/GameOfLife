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

	inline bool operator==(const Life& right)
	{
		return (x == right.x) && (y == right.y);
	}
};

struct CompareLife
{
	inline bool operator()(const Life* left, const Life* right) const
	{
		//if (left->x < right->x) {
		//	return true;
		//}

		//if (left->y < right->y) {
		//	return true;
		//}
		//return false;
//		return (left->x < right->x) && (left->y < right->y);

		if (left->x < right->x) {
			return true;
		}
		if ((left->x == right->x) && (left->y < right->y)) {
			return true;
		}
		return false;
	}
};

using LifeSet = std::set<Life*, CompareLife>;
using LifeAllocator = Allocator<Life>;

//class Life
//{
//public:
//	Life(i64 x, i64 y) : generation_(0), x_(x), y_(y)
//	{
//
//	}
//
//	// get the x and y
//	inline i64 x() const
//	{
//		return x_;
//	}
//
//	inline i64 y() const
//	{
//		return y_;
//	}
//
//	inline bool is_me(const Life& life) const
//	{
//		return (x_ == life.x_) && (y_ == life.y_);
//	}
//
//	inline bool is_neighbor(const Life & other) const
//	{
//		return (std::abs(x_ - other.x_) <= 1) && (std::abs(y_ - other.y_) <= 1);
//	}
//
//public:
//	int generation_;
//	i64 x_;
//	i64 y_;
//};
//
//using LifeVector = std::vector<Life>;
