#pragma once

#include <glm/mat2x2.hpp>
#include <glm/mat3x3.hpp>
#include <glm/mat4x4.hpp>

#include <ostream>

namespace aw
{

typedef glm::mat4 Mat4;
typedef glm::mat3 Mat3;
typedef glm::mat2 Mat2;

std::ostream& operator<<(std::ostream& stream, const Mat2& matrix);
std::ostream& operator<<(std::ostream& stream, const Mat3& matrix);
std::ostream& operator<<(std::ostream& stream, const Mat4& matrix);

} // namespace aw
