#include <aw/gui/widgets/list.hpp>

namespace aw::gui
{
List::List(const GUI& gui) : Bin(gui)
{
  setPadding(Padding(2.f));
}

ListItem::SPtr List::addItem(std::string text, std::string id)
{
  // Lazy initialization, because we cannot create shared from this in constructor, which sucks
  if (!getChild())
  {
    auto panel = std::make_shared<Panel>(getGUI());
    panel->setPadding(Padding(10.f));
    mChildContainer = std::make_shared<LinearContainer>(getGUI(), Orientation::Vertical);
    mChildContainer->setSpaceBetweenElements(3.f);
    panel->setChild(mChildContainer);
    setChild(panel);
  }
  auto newChild = std::make_shared<ListItem>(getGUI(), text, id);
  newChild->onSelect = [this](Widget& widget) { selectedChild(widget); };
  mChildContainer->addChild(newChild);
  return newChild;
}

void List::selectItem(std::string_view id)
{
  for (auto& child : mChildContainer->getChildren())
  {
    auto* item = static_cast<aw::gui::ListItem*>(child.get());
    if (item->getId() == id)
    {
      item->select();
    }
  }
}

void List::selectedChild(Widget& widget)
{
  deselectOtherChilds(&widget);
  if (onChildSelect)
    onChildSelect(static_cast<ListItem&>(widget));
}

void List::deselectOtherChilds(const Widget* childToExclude)
{
  for (auto& child : mChildContainer->getChildren())
  {
    if (child.get() != childToExclude)
      child->deselect();
  }
}

ListItem::SPtr List::getLastItem() const
{
  return std::static_pointer_cast<ListItem>(mChildContainer->getChildren().back());
}
} // namespace aw::gui
