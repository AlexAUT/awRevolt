#include <aw/gui/widgets/menu.hpp>

#include <aw/gui/gui.hpp>
#include <aw/gui/renderer/nanovgRenderer.hpp>

namespace aw::gui
{
void Menu::render(Vec2 parentPos)
{
  LinearContainer::render(parentPos);
  getGUI().getRenderer().render(*this);
}
}
