#pragma once

#include <memory>

class Gui : std::enable_shared_from_this<Gui>
{
public:

};

using GuiPtr = std::shared_ptr<Gui>;