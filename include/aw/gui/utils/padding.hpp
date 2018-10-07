#pragma once

#include <aw/utils/math/vector.hpp>

namespace aw::gui
{
struct Padding
{
  Padding() = default;
  Padding(float val) : top(val), right(val), bottom(val), left(val) {}

  Padding(float top_, float right_, float bottom_, float left_) : top(top_), right(right_), bottom(bottom_), left(left_)
  {
  }

  Padding(float topBottom, float rightLeft) : top(topBottom), right(rightLeft), bottom(topBottom), left(rightLeft) {}

  float top{0.f};
  float right{0.f};
  float bottom{0.f};
  float left{0.f};
};
} // namespace aw::gui
