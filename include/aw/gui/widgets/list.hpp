#pragma once

#include <aw/gui/widgets/linearContainer.hpp>
#include <aw/gui/widgets/listItem.hpp>
#include <aw/gui/widgets/panel.hpp>
#include <aw/gui/widgets/widget.hpp>

namespace aw::gui
{
class List : public Bin
{
public:
  using SPtr = std::shared_ptr<List>;

  using SelectChildCallack = std::function<void(ListItem&)>;

public:
  List(const GUI& gui);
  virtual ~List() = default;

  ListItem::SPtr addItem(std::string text, std::string id);
  ListItem::SPtr getLastItem() const;

  void deselectSelectedChild();
  void selectItem(std::string_view id);

  SelectChildCallack onChildSelect;

private:
  void selectedChild(Widget& widget);
  void deselectOtherChilds(const Widget* child);

private:
  LinearContainer::SPtr mChildContainer;
};
} // namespace aw::gui
