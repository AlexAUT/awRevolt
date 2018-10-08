#pragma once

#include <aw/gui/widgets/container.hpp>

#include <aw/gui/utils/orientation.hpp>

#include <vector>

namespace aw::gui
{
class LinearContainer : public Container
{
public:
  LinearContainer(const GUI& gui, Orientation orientation) : Container(gui), mOrientation(orientation) {}
  virtual ~LinearContainer() = default;

  void addChild(Widget::SPtr newChild, float weight = 1.f);

  virtual void updateLayout() override;

private:
private:
  Orientation mOrientation;

  std::vector<float> mWeights;
};
} // namespace aw::gui
