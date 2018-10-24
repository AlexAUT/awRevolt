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

public:
  List(const GUI& gui);
  virtual ~List() = default;

  ListItem::SPtr addItem(std::string text, std::string id);

private:
private:
  LinearContainer::SPtr mChildContainer;
};
} // namespace aw::gui
