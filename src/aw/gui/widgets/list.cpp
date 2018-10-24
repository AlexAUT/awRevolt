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
  mChildContainer->addChild(newChild);
  return newChild;
}
} // namespace aw::gui
