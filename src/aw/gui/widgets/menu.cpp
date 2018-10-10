#include <aw/gui/widgets/menu.hpp>

#include <aw/gui/gui.hpp>
#include <aw/gui/renderer/nanovgRenderer.hpp>
#include <aw/gui/utils/eventConvert.hpp>

#include <aw/utils/log.hpp>

namespace aw::gui
{
void Menu::render(Vec2 parentPos)
{
  Widget::render(parentPos);
  getGUI().getRenderer().render(*this);
  // Render childs
  LinearContainer::render(parentPos);
}

void Menu::setSelectedChild(Widget* child, Widget* caller)
{
  // The caller is only allowed to change it to nullptr if he is the selected one
  if (!child && caller != mSelectedChild.get())
    return;

  if (child)
  {
    mSelectedChild = child->getSharedPtr();
    getGUI().setSelectedWidget(getSharedPtr());
  }
  else
  {
    mSelectedChild = nullptr;
    getGUI().setSelectedWidget(nullptr);
  }
}
}
