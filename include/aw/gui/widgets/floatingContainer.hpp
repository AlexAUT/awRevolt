#pragma once

#include <aw/gui/widgets/container.hpp>

namespace aw::gui
{
class FloatingContainer : public Container
{
public:
  enum class BoundsPolicy
  {
    NoChecks, // Widget can be placed outside of container
    Relaxed,  // Widget may overlap with the border, but cannot escape completly
    Strict    // Widget are kept completly inside the container
  };

public:
  FloatingContainer(const GUI& gui, BoundsPolicy boundsPolicy = BoundsPolicy::Strict)
      : Container(gui), mBoundsPolicy(boundsPolicy)
  {
  }
  ~FloatingContainer() = default;

  virtual void updateLayout();

  void addChild(const Widget::SPtr& ptr, Vec2 pos, Vec2 size)
  {
    mChildren.push_back(ptr);
    ptr->setParent(getSharedPtr());
    ptr->setRelativePosition(pos);
    ptr->setSize(size);
  }

  void setBoundsPolicy(BoundsPolicy policy);
  BoundsPolicy getBoundsPolicy() const { return mBoundsPolicy; }

private:
private:
  BoundsPolicy mBoundsPolicy;
};
} // namespace aw::gui
