#pragma once

#include <aw/gui/utils/signal.hpp>
#include <aw/gui/widgets/linearContainer.hpp>
#include <aw/gui/widgets/listItem.hpp>
#include <aw/gui/widgets/panel.hpp>
#include <aw/gui/widgets/widget.hpp>

#include <aw/utils/log.hpp>

namespace aw::gui
{
class List : public Bin
{
public:
  AW_GUI_CLASS_NAME(List)
  using SPtr = std::shared_ptr<List>;

  using SelectChildCallack = aw::gui::Signal<void(ListItem&)>;

public:
  List(const GUI& gui);
  virtual ~List() = default;

  ListItem::SPtr addItem(std::string text, std::string id);
  ListItem::SPtr addItem(std::string text, std::string id, size_t index);
  ListItem::SPtr addItemAfter(std::string text, std::string id, ListItem* addAfter);
  ListItem::SPtr getLastItem() const;

  bool removeItem(ListItem* item);
  bool removeItem(std::string_view id);

  ListItem* getItem(std::string_view id);

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
