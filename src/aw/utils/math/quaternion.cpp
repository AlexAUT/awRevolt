#include <aw/utils/math/quaternion.hpp>

namespace aw
{
std::ostream& operator<<(std::ostream& stream, const Quaternion& quat)
{
  stream << "Quat(" << quat.x << "," << quat.y << "," << quat.z << ":" << quat.w << ")";
  return stream;
}
} // namespace aw
