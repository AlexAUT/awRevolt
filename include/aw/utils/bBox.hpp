#pragma once

#include <aw/utils/math/vector.hpp>

#include <glm/common.hpp>

#include <ostream>

namespace aw
{
class BBox
{
public:
  explicit BBox(float size);
  explicit BBox(Vec3 size);
  BBox(Vec3 origin, Vec3 extend);

  Vec3 min{0.f};
  Vec3 max{0.f};

  Vec3 getSize() const
  {
    return 0.5f * (max + min);
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
std::ostream& operator<<(std::ostream& stream, const BBox& box);
} // namespace aw
