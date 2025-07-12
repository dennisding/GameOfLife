#pragma once

#include "rectangle.hpp"

#include <vector>
#include <memory>

class RenderSet : std::enable_shared_from_this<RenderSet>
{
public:

public:
	TriangleSet triangles_;
	Color color_;
};

using RenderSetPtr = std::shared_ptr<RenderSet>;
using RenderSetVector = std::vector<RenderSetPtr>;