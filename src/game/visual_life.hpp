
#pragma once

#include "life.hpp"

#include <map>
#include <memory>

class VisualLife : std::enable_shared_from_this<VisualLife>
{
public:

private:
};

using VisualLifePtr = std::shared_ptr<VisualLife>;
using VisualLifeMap = std::map<Life, VisualLifePtr>;
