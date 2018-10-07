#pragma once

#include <aw/gui/widgets/container.hpp>

namespace aw::gui
{
class FloatingContainer : public Container
{
public:
  FloatingContainer(const GUI& gui) : Container(gui) {}
  ~FloatingContainer() = default;

  void addChild(const Widget::SPtr& ptr, Vec2 pos, Vec2 size)
  {
    ptr->setParent(getSharedPtr());
    ptr->setRelativePosition(pos);
    ptr->setSize(size);
    mChildren.push_back(ptr);
  }

private:
private:
};
} // namespace aw::gui
