#pragma once

#include <aw/utils/math/matrix.hpp>
#include <aw/utils/math/vector.hpp>

#include <array>

namespace aw
{
namespace frustum
{
std::array<Vec3, 8> split(float clipspaceNear, float clipspaceFar, const Mat4& inverseViewProj);
}

} // namespace aw
