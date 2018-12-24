#include <aw/utils/math/vector.hpp>

std::ostream& operator<<(std::ostream& stream, const aw::Vec2& vec)
{
  stream << "(" << vec.x << "," << vec.y << ")";
  return stream;
}

std::ostream& operator<<(std::ostream& stream, const aw::Vec2i& vec)
{
  stream << "(" << vec.x << "," << vec.y << ")";
  return stream;
}

std::ostream& operator<<(std::ostream& stream, const aw::Vec2u& vec)
{
  stream << "(" << vec.x << "," << vec.y << ")";
  return stream;
}

std::ostream& operator<<(std::ostream& stream, const aw::Vec3& vec)
{
  stream << "(" << vec.x << "," << vec.y << "," << vec.z << ")";
  return stream;
}

std::ostream& operator<<(std::ostream& stream, const aw::Vec3i& vec)
{
  stream << "(" << vec.x << "," << vec.y << "," << vec.z << ")";
  return stream;
}

std::ostream& operator<<(std::ostream& stream, const aw::Vec4& vec)
{
  stream << "(" << vec.x << "," << vec.y << "," << vec.z << "," << vec.w << ")";
  return stream;
}

std::ostream& operator<<(std::ostream& stream, const aw::Vec4i& vec)
{
  stream << "(" << vec.x << "," << vec.y << "," << vec.z << "," << vec.w << ")";
  return stream;
}

