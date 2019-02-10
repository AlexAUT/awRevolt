#include <aw/gui/widgets/list.hpp>

namespace aw::gui
{
List::List(const GUI& gui) : Bin(gui) {}

ListItem::SPtr List::addItem(std::string text, std::string id)
{
  auto index = mChildContainer ? mChildContainer->getChildren().size() : 0;
  return addItem(text, id, index);
}

ListItem::SPtr List::addItem(std::string text, std::string id, size_t index)
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
  newChild->onClick.connect([this](Widget& widget) { selectedChild(widget); });
  mChildContainer->addChildAt(index, newChild);
  return newChild;
}

ListItem::SPtr List::addItemAfter(std::string text, std::string id, ListItem* addAfter)
{
  if (getChild())
  {
    const auto& childs = mChildContainer->getChildren();
    for (auto i = 0u; i < childs.size(); i++)
    {
      if (childs[i].get() == addAfter)
      {
        return addItem(text, id, i + 1);
      }
    }
  }
  // Add as last if first or addAfter is not present
  return addItem(text, id);
}

bool List::removeItem(ListItem* item)
{
  return mChildContainer->removeChild(item);
}

bool List::removeItem(std::string_view id)
{
  return removeItem(getItem(id));
}

void List::deselectSelectedChild()
{
  deselectOtherChilds(nullptr);
}

ListItem* List::getItem(std::string_view id)
{
  for (auto& it : mChildContainer->getChildren())
  {
    auto* ptr = static_cast<ListItem*>(it.get());
    if (ptr->getId() == id)
      return static_cast<ListItem*>(it.get());
  }
  return nullptr;
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
