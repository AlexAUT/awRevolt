#pragma once

#include <aw/gui/widgets/widget.hpp>

#include <vector>

namespace aw::gui
{
class Container : public Widget
{
public:
  using ChildVector = std::vector<Widget::SPtr>;

public:
  Container(const GUI& gui) : Widget(gui) {}
  virtual ~Container() = default;

  const ChildVector& getChildren() const { return mChildren; }

  virtual void update(float delta) override;
  virtual void render(Vec2 parentPos) override;
  virtual bool processEvent(const WindowEvent& event) override;

  virtual void updateLayout() override;

  virtual void invalidateLayout() override;

private:
protected:
  ChildVector mChildren;
};
} // namespace aw::gui
