#pragma once

#include <aw/gui/widgets/widget.hpp>

namespace aw::gui
{
class Bin : public Widget
{
public:
  Bin(const GUI& gui) : Widget(gui) {}
  virtual ~Bin() = default;

  virtual void update(float delta) override;
  virtual bool processEvent(const WindowEvent& event) override;
  virtual void render(Vec2 parentPos) override;

  virtual void updateLayout() override;
  virtual Vec2 getMinimalSize() const override;

  void setChild(Widget::SPtr child);

  const Widget::SPtr& getChild() const { return mChild; }

private:
  Vec2 calculateChildRelPosition() const;
  Vec2 calculateChildSize() const;

private:
  Widget::SPtr mChild{nullptr};
};
} // namespace aw::gui
