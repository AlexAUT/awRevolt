#include <aw/utils/spatial/AABB.hpp>

namespace aw
{
AABB::AABB(float size) : min(-0.5f * size), max(0.5f * size)
{
}

AABB::AABB(Vec3 size) : min(-0.5f * size), max(0.5f * size)
{
}

AABB::AABB(Vec3 origin, Vec3 extend) : min(origin - extend), max(origin + extend)
{
}

std::ostream& operator<<(std::ostream& stream, const AABB& box)
{
  stream << "AABB{ min: " << box.min << ", max: " << box.max << "}";
  return stream;
}

// Static factories

AABB AABB::createFromTransform(const AABB& box, const Mat4& transform)
{
  // we have to transform the eight points and add it to the new
  AABB result;

  auto size = box.getSize();

  result += transform * Vec4(box.min, 1.0);
  result += transform * Vec4(box.max, 1.0);
  result += transform * Vec4(box.min + Vec3{size.x, 0.f, 0.f}, 1.0f);
  result += transform * Vec4(box.min + Vec3{size.x, size.y, 0.f}, 1.0f);
  result += transform * Vec4(box.min + Vec3{size.x, 0.f, size.z}, 1.0f);
  result += transform * Vec4(box.min + Vec3{0.f, size.y, 0.f}, 1.0f);
  result += transform * Vec4(box.min + Vec3{0.f, size.y, size.z}, 1.0f);
  result += transform * Vec4(box.min + Vec3{0.f, 0.f, size.z}, 1.0f);

  return result;
}

} // namespace aw
