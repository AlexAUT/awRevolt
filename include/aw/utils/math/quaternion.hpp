#pragma once

#include <glm/gtc/quaternion.hpp>

#include <ostream>

namespace aw
{
typedef glm::quat Quaternion;

std::ostream& operator<<(std::ostream& stream, const Quaternion& vec);
} // namespace aw
