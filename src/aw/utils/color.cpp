#include <aw/utils/color.hpp>

namespace aw
{
void Color::tint(float amount)
{
  r = r - r * amount;
  g = g - g * amount;
  b = b - b * amount;
}

void Color::shade(float amount)
{
  r = r + (1.f - r) * amount;
  g = g + (1.f - g) * amount;
  b = b + (1.f - b) * amount;
}
} // namespace aw
