
#include "view_port.hpp"

Viewport::Viewport(i64 x, i64 y, i64 width)
	: x_(x), y_(y), width_(width)
{

}

Viewport::~Viewport()
{

}

void Viewport::set_center(i64 x, i64 y)
{
	x_ = x;
	y_ = y;
}
