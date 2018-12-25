#pragma once

#include <aw/utils/math/vector.hpp>

#include <ostream>

namespace aw
{
struct Ray
{
  Vec3 origin;
  Vec3 dir;
  Vec3 invDir;

  Ray(aw::Vec3 origin, aw::Vec3 dir) : origin(origin), dir(dir), invDir(1.f / dir) {}
};
} // namespace aw

std::ostream& operator<<(std::ostream& stream, const aw::Ray& ray);
