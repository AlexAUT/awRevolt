#pragma once

#include <aw/graphics/core/color.hpp>
#include <aw/utils/math/vector.hpp>

namespace aw
{
struct DirectionalLight
{
  Vec3 direction;
  Color color;
  float energy;
};
} // namespace aw
