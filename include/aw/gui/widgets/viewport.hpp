#pragma once

#include <aw/gui/widgets/bin.hpp>

namespace aw::gui
{
class Viewport : public Widget
{
public:
  AW_GUI_CLASS_NAME(Viewport)
  using SPtr = std::shared_ptr<Viewport>;

public:
  Viewport(const GUI& gui);
  virtual ~Viewport() = default;

  virtual bool processEvent(const aw::WindowEvent& event) override;
  virtual void render() override;

  virtual void updateLayout(Vec2 parentPos) override;

  void setChild(Widget::SPtr child);

  Widget::SPtr& getChild() { return mChild; }
  const Widget::SPtr& getChild() const { return mChild; }

  void setHorizontalOffset(float value);
  float getHorizontalOffset() const { return mHorizontalOffset; }

  void setVerticalOffset(float value);
  float getVertialOffset() const { return mVerticalOffset; }

  virtual void invalidateLayout() override;

private:
private:
  Widget::SPtr mChild{nullptr};

  float mHorizontalOffset{0.f};
  float mVerticalOffset{0.f};
};
} // namespace aw::gui
