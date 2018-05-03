#include <aw/utils/math/vector.hpp>

namespace aw
{

std::ostream& operator<<(std::ostream& stream, const Vec2& vec)
{
  stream << "(" << vec.x << "," << vec.y << ")";
  return stream;
}

std::ostream& operator<<(std::ostream& stream, const Vec2i& vec)
{
  stream << "(" << vec.x << "," << vec.y << ")";
  return stream;
}

std::ostream& operator<<(std::ostream& stream, const Vec3& vec)
{
  stream << "(" << vec.x << "," << vec.y << "," << vec.z << ")";
  return stream;
}

std::ostream& operator<<(std::ostream& stream, const Vec3i& vec)
{
  stream << "(" << vec.x << "," << vec.y << "," << vec.z << ")";
  return stream;
}

std::ostream& operator<<(std::ostream& stream, const Vec4& vec)
{
  stream << "(" << vec.x << "," << vec.y << "," << vec.z << "," << vec.w << ")";
  return stream;
}

std::ostream& operator<<(std::ostream& stream, const Vec4i& vec)
{
  stream << "(" << vec.x << "," << vec.y << "," << vec.z << "," << vec.w << ")";
  return stream;
}

} // namespace aw
