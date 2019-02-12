#pragma once

#include <aw/gui/widgets/viewport.hpp>

namespace aw::gui
{
class ScrollableBin : public Viewport
{
public:
  AW_GUI_CLASS_NAME(ScrollableBin)

  ScrollableBin(const GUI& gui);
  virtual ~ScrollableBin() = default;

  virtual bool processEvent(const aw::WindowEvent& event) override;
  virtual void render() override;

  void setChild(Widget::SPtr widget);
  Widget::SPtr& getChild() { return mViewport->getChild(); }
  const Widget::SPtr getChild() const { return mViewport->getChild(); }

  void updateLayout(Vec2 parentPos) override;

  virtual void invalidateLayout() override;

private:
  Viewport::SPtr mViewport;
};
} // namespace aw::gui
