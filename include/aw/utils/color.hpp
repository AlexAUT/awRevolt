#pragma once

#include <aw/utils/math/vector.hpp>

#include <ostream>

namespace aw
{
struct Color
{
public:
  float r, g, b, a;
};

Color tintColor(Color color, float amount);
Color shadeColor(Color color, float amount);
} // namespace aw

std::ostream& operator<<(std::ostream&, const aw::Color&);
