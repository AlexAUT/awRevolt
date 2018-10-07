#pragma once

#include <aw/gui/utils/padding.hpp>
#include <aw/gui/widgets/widget.hpp>

namespace aw::gui
{
class Bin : public Widget
{
public:
  Bin(const GUI& gui, Padding padding = {0.f}) : Widget(gui), mPadding(padding) {}
  virtual ~Bin() = default;

  virtual void update(float delta) override;
  virtual bool processEvent(const WindowEvent& event) override;
  virtual void render(Vec2 parentPos) override;

  void setChild(Widget::SPtr child);
  void setPadding(Padding padding);

  const Widget::SPtr& getChild() const { return mChild; }
  Padding getPadding() const { return mPadding; }

private:
  Vec2 calculateChildRelPosition() const;
  Vec2 calculateChildSize() const;

private:
  Padding mPadding;
  Widget::SPtr mChild{nullptr};
};
} // namespace aw::gui
