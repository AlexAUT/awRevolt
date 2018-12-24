#include <aw/utils/math/quaternion.hpp>

std::ostream& operator<<(std::ostream& stream, const aw::Quaternion& quat)
{
  stream << "Quat(" << quat.x << "," << quat.y << "," << quat.z << ":" << quat.w << ")";
  return stream;
} // namespace aw
