#include <aw/gui/widgets/listItem.hpp>

#include <aw/gui/gui.hpp>
#include <aw/gui/renderer/nanovgRenderer.hpp>

namespace aw::gui
{
ListItem::ListItem(const GUI& gui, std::string text, std::string id) : Label(gui, text), mId(id)
{
  setSelectable(true);
}

void ListItem::render(Vec2 parentPos)
{
  Widget::render(parentPos);
  getGUI().getRenderer().render(*this);
}
} // namespace aw::gui
