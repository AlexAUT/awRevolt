#pragma once

#include <aw/gui/widgets/container.hpp>

#include <aw/gui/style/orientation.hpp>
#include <aw/gui/style/padding.hpp>

#include <vector>

namespace aw::gui
{
class LinearContainer : public Container
{
public:
  using SPtr = std::shared_ptr<LinearContainer>;

public:
  LinearContainer(const GUI& gui, Orientation orientation) : Container(gui), mOrientation(orientation) {}
  virtual ~LinearContainer() = default;

  void addChild(Widget::SPtr newChild, float weight = 1.f);

  void setSpaceBetweenElements(float space);
  float getSpaceBetweenElements() const { return mSpaceBetweenElements; }

  virtual void updateLayout() override;
  virtual Vec2 getMinimalSize() const override;

private:
  Vec2 getDynamicAxisPadding() const;
  Vec2 getStaticAxisPadding() const;

private:
  Orientation mOrientation;

  float mSpaceBetweenElements{0.f};

  std::vector<float> mWeights;

  mutable Vec2 mMinimalSizeCache{0.f};
};
} // namespace aw::gui
