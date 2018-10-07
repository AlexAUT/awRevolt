#include <aw/gui/widgets/screen.hpp>

namespace aw::gui
{
Screen::Screen(const GUI& gui, Vec2 pos, Vec2 size) : FloatingContainer(gui)
{
  setRelativePosition(pos);
  setGlobalPosition(pos);
  setSize(size);
}
} // namespace aw::gui
