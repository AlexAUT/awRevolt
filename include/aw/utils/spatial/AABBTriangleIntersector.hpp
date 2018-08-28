#pragma once

#include <aw/utils/math/vector.hpp>

namespace aw
{

class AABB;

class AABBTriangleIntersector
{
public:
  bool operator()(const AABB& bounds, Vec3 t1, Vec3 t2, Vec3 t3);
};
} // namespace aw
