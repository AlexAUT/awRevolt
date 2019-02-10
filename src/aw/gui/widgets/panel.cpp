#include <aw/gui/widgets/panel.hpp>

#include <aw/gui/gui.hpp>
#include <aw/gui/renderer/nanovgRenderer.hpp>

namespace aw::gui
{
void Panel::render()
{
  Widget::render();
  getGUI().getRenderer().render(*this);
  Bin::render();
}
} // namespace aw::gui
