#pragma once

#include <aw/gui/widgets/container.hpp>

#include <aw/gui/utils/orientation.hpp>

namespace aw::gui
{
class LinearContainer : public Container
{
public:
  LinearContainer(const GUI& gui, Orientation orientation) : Container(gui), mOrientation(orientation) {}
  virtual ~LinearContainer() = default;

  void addChild(Widget::SPtr newChild, float weight = 1.f);

private:
private:
  Orientation mOrientation;
};
} // namespace aw::gui
