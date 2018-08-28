#pragma once

#include <aw/utils/spatial/AABB.hpp>
#include <aw/utils/spatial/AABBTriangleIntersector.hpp>

#include <aw/utils/math/vector.hpp>

namespace aw
{

template <typename VectorType>
struct AABBPointIntersector
{
  bool operator()(AABB box, VectorType point)
  {
    return (point.x >= box.min.x && point.x <= box.max.x) && (point.y >= box.min.y && point.y <= box.max.y) &&
           (point.z >= box.min.z && point.z <= box.max.z);
  }
};

struct AABBAABBIntersector
{
  bool operator()(AABB a, AABB b)
  {
    return (a.min.x <= b.max.x && a.max.x >= b.min.x) && (a.min.y <= b.max.y && a.max.y >= b.min.y) &&
           (a.min.z <= b.max.z && a.max.z >= b.min.z);
  }
};
} // namespace aw
