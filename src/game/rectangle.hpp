#pragma once

#include <memory>
#include <vector>

//#include "position.hpp"
#include "color.hpp"

//struct Rectangle
//{
//	Position position_;
//	Color color_;
//};

struct TriangleSet
{
public:
	void add_rectangle(float x, float y, float xdelta, float ydelta);

public:
	std::vector<float> vertexs_;
};