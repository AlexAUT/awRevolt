#pragma once

#include <aw/utils/math/vector.hpp>

#include <ostream>

namespace aw
{
struct Color
{
public:
  float r, g, b, a;

  template <class Archive>
  void serialize(Archive& archive);
};

Color tintColor(Color color, float amount);
Color shadeColor(Color color, float amount);
} // namespace aw

std::ostream& operator<<(std::ostream&, const aw::Color&);

namespace aw
{
#ifndef CEREAL_NVP
#define CEREAL_NVP(x)
#endif
template <typename Archive>
void Color::serialize(Archive& archive)
{
  archive(CEREAL_NVP(r));
  archive(CEREAL_NVP(g));
  archive(CEREAL_NVP(b));
  archive(CEREAL_NVP(a));
}
} // namespace aw

