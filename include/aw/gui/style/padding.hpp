#pragma once

#include <aw/utils/math/vector.hpp>
#include <aw/utils/types.hpp>

#include <ostream>

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

  // Order same as constructor, can be useful to avoid ifs
  float operator[](size_t index) const { return *(&top + index); }

  float horizontal() const { return left + right; }
  float vertical() const { return top + bottom; }
  Vec2 horizontalVertical() const { return {horizontal(), vertical()}; }

  Vec2 leftTop() const { return {left, top}; }
  Vec2 rightBottom() const { return {right, bottom}; }
};
} // namespace aw::gui

inline std::ostream& operator<<(std::ostream& stream, const aw::gui::Padding& p)
{
  stream << "Padding: {"
         << "t: " << p.top << ", r: " << p.right << ", b: " << p.bottom << ", l: " << p.left << " }";
  return stream;
}
