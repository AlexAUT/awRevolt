#pragma once

#include <aw/gui/widgets/linearContainer.hpp>

namespace aw::gui
{
class Menu : public LinearContainer
{
public:
  Menu(const GUI& gui) : LinearContainer(gui, Orientation::Horizontal) {}

private:
private:
};
} // namespace aw::gui
