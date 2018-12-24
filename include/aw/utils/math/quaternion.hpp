#pragma once

#include <glm/gtc/quaternion.hpp>

#include <ostream>

namespace aw
{
typedef glm::quat Quaternion;
} // namespace aw

std::ostream& operator<<(std::ostream& stream, const aw::Quaternion& vec);
