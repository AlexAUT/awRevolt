#pragma once

#include <aw/utils/math/vector.hpp>

namespace aw
{
class Color
{
public:
  Color(float r, float g, float b, float a) : r(r), g(g), b(b), a(a) {}

  void tint(float amount);
  void shade(float amount);

public:
  float r, g, b, a;
};
} // namespace aw
