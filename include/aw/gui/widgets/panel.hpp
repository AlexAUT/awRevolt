#pragma once

#include <aw/gui/widgets/bin.hpp>

namespace aw::gui
{
class Panel : public Bin
{
public:
  using SPtr = std::shared_ptr<Panel>;

public:
  Panel(const GUI& gui) : Bin(gui) {}
  virtual ~Panel() = default;

  virtual void render() override;

private:
private:
};
} // namespace aw::gui
