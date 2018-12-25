#include <aw/utils/spatial/intersectors/rayIntersectors.hpp>

namespace aw
{
bool RayAABBIntersector::operator()(Ray r, AABB b)
{
  // Source: from https://tavianator.com/fast-branchless-raybounding-box-intersections-part-2-nans/
  float t1 = (b.min[0] - r.origin[0]) * r.invDir[0];
  float t2 = (b.max[0] - r.origin[0]) * r.invDir[0];

  float tmin = glm::min(t1, t2);
  float tmax = glm::max(t1, t2);

  for (int i = 1; i < 3; ++i)
  {
    t1 = (b.min[i] - r.origin[i]) * r.invDir[i];
    t2 = (b.max[i] - r.origin[i]) * r.invDir[i];

    tmin = glm::max(tmin, glm::min(glm::min(t1, t2), tmax));
    tmax = glm::min(tmax, glm::max(glm::max(t1, t2), tmin));
  }

  return tmax > glm::max(tmin, 0.0f);
}

bool RayAABBIntersectorFast::operator()(Ray r, AABB b)
{
  // Source: from https://tavianator.com/fast-branchless-raybounding-box-intersections-part-2-nans/
  float t1 = (b.min[0] - r.origin[0]) * r.invDir[0];
  float t2 = (b.max[0] - r.origin[0]) * r.invDir[0];

  float tmin = glm::min(t1, t2);
  float tmax = glm::max(t1, t2);

  for (int i = 1; i < 3; ++i)
  {
    t1 = (b.min[i] - r.origin[i]) * r.invDir[i];
    t2 = (b.max[i] - r.origin[i]) * r.invDir[i];

    tmin = glm::max(tmin, glm::min(t1, t2));
    tmax = glm::min(tmax, glm::max(t1, t2));
  }

  return tmax > glm::max(tmin, 0.0f);
}
} // namespace aw
