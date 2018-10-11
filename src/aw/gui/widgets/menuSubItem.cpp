#include <aw/gui/widgets/menuSubItem.hpp>

#include <aw/gui/gui.hpp>
#include <aw/gui/renderer/nanovgRenderer.hpp>

namespace aw::gui
{
MenuSubItem::MenuSubItem(const GUI& gui, Menu& menu, std::string text) : Label(gui, text), mMenu(menu)
{
  setAlignment({AlignmentH::Left, AlignmentV::Middle});
  setPadding({4.f, 10.f});

  auto style = getGUI().getTextStyles().getStyle("menuItem");
  assert(style);
  setTextLayout(style);
}

void MenuSubItem::render(Vec2 parentPos)
{
  Widget::render(parentPos);
  getGUI().getRenderer().render(*this);
}
} // namespace aw::gui
