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

  void setOuterPadding(Padding padding);
  void setSpaceBetweenElements(float space);

  void addChild(Widget::SPtr newChild, float weight = 1.f);

  Padding getOuterPadding() const { return mOuterPadding; }
  float getSpaceBetweenElements() const { return mSpaceBetweenElements; }

  virtual void updateLayout() override;
  virtual Vec2 getMinimalSize() const override;

private:
  Vec2 getOuterDynamicAxisPadding() const;
  Vec2 getOuterStaticAxisPadding() const;

private:
  Orientation mOrientation;

  Padding mOuterPadding{0.f};
  float mSpaceBetweenElements{0.f};

  std::vector<float> mWeights;

  mutable Vec2 mMinimalSizeCache{0.f};
};
} // namespace aw::gui
