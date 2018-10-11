#include <aw/gui/widgets/menu.hpp>

#include <aw/gui/gui.hpp>
#include <aw/gui/renderer/nanovgRenderer.hpp>
#include <aw/gui/utils/eventConvert.hpp>

namespace aw::gui
{
MenuItem::SPtr Menu::addMenuEntry(std::string text)
{
  auto item = std::make_shared<MenuItem>(getGUI(), *this, std::move(text));
  addChild(item, 0);
  return item;
}

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

  if (mSelectedChild && caller != mSelectedChild.get())
    mSelectedChild->deselect({0.f, 0.f});

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
