#pragma once

#include <memory>

class Surface : std::enable_shared_from_this<Surface>
{
public:

};

using SurfacePtr = std::shared_ptr<Surface>;

