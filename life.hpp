#pragma once

#include <cmath>
#include <vector>
#include <map>

#include "config.hpp"

class Life
{
public:
	Life(i64 x, i64 y) : generation_(0), x_(x), y_(y)
	{

	}

	// get the x and y
	inline i64 x() const
	{
		return x_;
	}

	inline i64 y() const
	{
		return y_;
	}

	inline bool is_me(const Life& life) const
	{
		return (x_ == life.x_) && (y_ == life.y_);
	}

	inline bool is_neighbor(const Life & other) const
	{
		return (std::abs(x_ - other.x_) <= 1) && (std::abs(y_ - other.y_) <= 1);
	}

public:
	int generation_;
	i64 x_;
	i64 y_;
};

using LifeVector = std::vector<Life>;
