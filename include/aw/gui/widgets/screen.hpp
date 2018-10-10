#pragma once

#include <aw/gui/widgets/bin.hpp>

namespace aw::gui
{
class Screen : public Bin
{
public:
  using SPtr = std::shared_ptr<Screen>;

public:
  Screen(const GUI& gui, Vec2 pos, Vec2 size);

private:
private:
};
} // namespace aw::gui
