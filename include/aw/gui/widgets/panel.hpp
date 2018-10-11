#pragma once

#include <aw/gui/widgets/bin.hpp>

namespace aw::gui
{
class Panel : public Bin
{
public:
  using SPtr = std::shared_ptr<Bin>;

public:
  Panel(const GUI& gui) : Bin(gui) {}
  virtual ~Panel() = default;

  virtual void render(Vec2 parentPos) override;

private:
private:
};
}
