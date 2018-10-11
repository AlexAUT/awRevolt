#pragma once

#include <aw/gui/widgets/linearContainer.hpp>

#include <aw/gui/widgets/menuItem.hpp>

namespace aw::gui
{
class Menu : public LinearContainer
{
public:
  Menu(const GUI& gui) : LinearContainer(gui, Orientation::Horizontal) {}

  MenuItem::SPtr addMenuEntry(std::string text);

  virtual void render(Vec2 parentPos) override;

  void setSelectedChild(Widget* child, Widget* caller);
  Widget* getSelectedChild() const { return mSelectedChild.get(); }

private:
private:
  Widget::SPtr mSelectedChild;
};
} // namespace aw::gui
