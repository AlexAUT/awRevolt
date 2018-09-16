#include <aw/utils/math/frustum.hpp>

namespace aw
{
namespace frustum
{
std::array<Vec3, 8> split(float clipspaceNear, float clipspaceFar, const Mat4& inverseViewProj)
{
  std::array<Vec3, 8> result = {Vec3(-1, 1, clipspaceNear),  Vec3(1, 1, clipspaceNear), Vec3(1, -1, clipspaceNear),
                                Vec3(-1, -1, clipspaceNear), Vec3(-1, 1, clipspaceFar), Vec3(1, 1, clipspaceFar),
                                Vec3(1, -1, clipspaceFar),   Vec3(-1, -1, clipspaceFar)};

  for (auto& v : result)
  {
    auto vProj = inverseViewProj * Vec4(v, 1.0f);
    v = vProj / vProj.w;
  }

  return result;
}

} // namespace frustum
} // namespace aw
