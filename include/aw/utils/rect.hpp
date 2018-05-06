#pragma once

#include <ostream>

namespace aw
{
template <typename T>
struct Rect
{
  T left;
  T bottom;
  T width;
  T height;

  Rect() = default;
  Rect(T left_, T bottom_, T width_, T height_) : left(left_), bottom(bottom_), width(width_), height(height_)
  {
  }

  template <typename T1>
  explicit Rect(const Rect<T1>& rect)
      : Rect(static_cast<T>(rect.left), static_cast<T>(rect.right), static_cast<T>(rect.width),
             static_cast<T>(rect.height))
  {
  }

  friend bool operator==(const Rect<T> r1, const Rect<T> r2)
  {
    return r1.left == r2.left && r1.bottom == r2.bottom && r1.width == r2.width && r1.height == r2.height;
  }

  friend bool operator!=(const Rect<T> r1, const Rect<T> r2)
  {
    return r1.left != r2.left || r1.bottom != r2.bottom || r1.width != r2.width || r1.height != r2.height;
  }

  friend std::ostream& operator<<(std::ostream& stream, const Rect<T>& rect)
  {
    stream << "Rect: (left:" << rect.left << ", right:" << rect.right << ", width" << rect.width << ", height"
           << rect.height << ")";
  }
};

typedef Rect<float> RectFloat;
typedef Rect<int> RectInt;
typedef Rect<unsigned> RectUInt;
} // namespace aw
