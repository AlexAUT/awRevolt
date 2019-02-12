#pragma once

#include <aw/gui/widgets/container.hpp>
#include <aw/utils/math/vector.hpp>

namespace aw::gui
{
class TileContainer : public Container
{
public:
  AW_GUI_CLASS_NAME(TileContainer)
  using SPtr = std::shared_ptr<TileContainer>;

public:
  TileContainer(const GUI& gui, Vec2u tileSize);

  void addChild(Widget::SPtr newChild);
  void addChildAt(size_t index, Widget::SPtr newChild);
  void addChildAfter(Widget* before, Widget::SPtr newChild);

  void removeAllChildren();

  virtual void updateLayout(Vec2 parentPos) override;
  virtual Vec2 getMinimalSize() const override;

private:
private:
  Vec2u mTileSize;

  Vec2 mMinimalSizeCache{0.f};
};
} // namespace aw::gui
