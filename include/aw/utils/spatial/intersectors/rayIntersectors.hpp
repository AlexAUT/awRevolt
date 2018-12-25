#pragma once

#include <aw/utils/spatial/AABB.hpp>
#include <aw/utils/spatial/ray.hpp>

namespace aw
{
struct RayAABBIntersector
{
  bool operator()(Ray ray, AABB box);
};

// Faster but not always correct (if ray origin is exactly on axis boundary)
struct RayAABBIntersectorFast
{
  bool operator()(Ray ray, AABB box);
};
} // namespace aw
