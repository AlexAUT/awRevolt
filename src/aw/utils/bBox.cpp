#include <aw/utils/bBox.hpp>

namespace aw
{
BBox::BBox(float size) : min(-0.5f * size), max(0.5f * size)
{
}

BBox::BBox(Vec3 size) : min(-0.5f * size), max(0.5f * size)
{
}

BBox::BBox(Vec3 origin, Vec3 extend) : min(origin - extend), max(origin - extend)
{
}

std::ostream& operator<<(std::ostream& stream, const BBox& box)
{
  stream << "BBox{ min: " << box.min << ", max: " << box.max << "}";
  return stream;
}

} // namespace aw
