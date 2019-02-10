#include <aw/gui/widgets/menuSubItem.hpp>

#include <aw/gui/gui.hpp>
#include <aw/gui/renderer/nanovgRenderer.hpp>

namespace aw::gui
{
MenuSubItem::MenuSubItem(const GUI& gui, Menu& menu, std::string text) : Label(gui, text), mMenu(menu)
{
  setAlignment({AlignmentH::Left, AlignmentV::Middle});
  setPadding({4.f, 10.f});
}

void MenuSubItem::render()
{
  Widget::render();
  getGUI().getRenderer().render(*this);
}
} // namespace aw::gui
