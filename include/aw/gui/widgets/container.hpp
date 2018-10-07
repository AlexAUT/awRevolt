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
  virtual ~Container() = default;

  const ChildVector& getChildren() const;

  virtual void update(float delta) override;
  virtual void render(NanovgRenderer& renderer, Vec2 parentPos) override;
  virtual bool processEvent(const WindowEvent& event) override;

private:
protected:
  ChildVector mChildren;
};
} // namespace aw::gui
