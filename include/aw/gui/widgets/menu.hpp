#pragma once

#include <aw/gui/widgets/linearContainer.hpp>

#include <aw/gui/widgets/menuItem.hpp>

namespace aw::gui
{
class Menu : public LinearContainer
{
public:
  using SPtr = std::shared_ptr<Menu>;

public:
  Menu(const GUI& gui) : LinearContainer(gui, Orientation::Horizontal) { setConsumeEvent(true); }

  MenuItem::SPtr addMenuEntry(std::string text);

  virtual void render() override;

  void setSelectedChild(Widget* child, Widget* caller);
  Widget* getSelectedChild() const { return mSelectedChild.get(); }

private:
private:
  Widget::SPtr mSelectedChild;
};
} // namespace aw::gui
