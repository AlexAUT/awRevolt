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

  // If you use a floating layout inside a dynamic container (e.g. linearContainer) call gui.updateLayout() before
  // adding childs, or otherwise this container will have no size and therefore the BoundsPolicy will mess up the
  // children of this container!
  void addChild(const Widget::SPtr& ptr, Vec2 pos, Vec2 size)
  {
    mChildren.push_back(std::move(ptr));
    mChildren.back()->setParent(getSharedPtr());
    mChildren.back()->setRelativePosition(pos);
    mChildren.back()->setSize(size);
  }

  void setBoundsPolicy(BoundsPolicy policy);
  BoundsPolicy getBoundsPolicy() const { return mBoundsPolicy; }

  virtual void updateLayout() override;
  virtual Vec2 getMinimalSize() const override;

private:
private:
  BoundsPolicy mBoundsPolicy;

  mutable Vec2 mMinimalSizeCache{0.f};
};
} // namespace aw::gui
