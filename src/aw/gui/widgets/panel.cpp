#include <aw/gui/widgets/panel.hpp>

#include <aw/gui/gui.hpp>
#include <aw/gui/renderer/nanovgRenderer.hpp>

namespace aw::gui
{
void Panel::render(Vec2 parentPos)
{
  Widget::render(parentPos);
  getGUI().getRenderer().render(*this);
  Bin::render(parentPos);
}
}
