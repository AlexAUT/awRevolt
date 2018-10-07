#include <aw/gui/widgets/screen.hpp>

namespace aw::gui
{
Screen::Screen(Vec2 pos, Vec2 size)
{
  setRelativePosition(pos);
  setGlobalPosition(pos);
  setSize(size);
}
} // namespace aw::gui
