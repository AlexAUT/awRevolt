#pragma once

#include <aw/utils/math/matrix.hpp>
#include <aw/utils/math/vector.hpp>

#include <glm/common.hpp>

#include <limits>
#include <ostream>

namespace aw
{
class AABB
{
public:
  static AABB createFromTransform(const AABB& box, const Mat4& tranfrom);

public:
  AABB() = default;
  explicit AABB(float size);
  explicit AABB(Vec3 size);
  AABB(Vec3 origin, Vec3 extend);

  Vec3 min{std::numeric_limits<float>::max()};
  Vec3 max{std::numeric_limits<float>::lowest()};

  Vec3 getSize() const
  {
    return max - min;
  }

  Vec3 getExtend() const
  {
    return getSize() * 0.5f;
  }

  Vec3 getCenter() const
  {
    return min + getSize() * 0.5f;
  }

  void operator+=(const Vec3& point)
  {
    min = glm::min(min, point);
    max = glm::max(max, point);
  }

  void addPoint(const Vec3& point)
  {
    (*this) += point;
  }

private:
};
std::ostream& operator<<(std::ostream& stream, const AABB& box);
} // namespace aw
