#pragma once

#include <aw/graphics/core/geometry.hpp>

#include <aw/utils/typeChecks.hpp>

namespace aw
{
namespace geo
{
namespace priv
{
MEMBER_PRESENT_CHECKER(position, Vec3)
MEMBER_PRESENT_CHECKER(normal, Vec3)
MEMBER_PRESENT_CHECKER(texCoord, Vec2)

template <typename VertexType>
void setVertex(VertexType& vertex, Vec3 pos, Vec3 normal, Vec2 texCoord)
{
  if constexpr (Has_position<VertexType>{})
    vertex.position = pos;
  if constexpr (Has_normal<VertexType>{})
    vertex.normal = normal;
  if constexpr (Has_texCoord<VertexType>{})
    vertex.texCoord = texCoord;
}
} // namespace priv

template <typename VertexType>
std::array<VertexType, 6 * 6> cube(Vec3 center, Vec3 size)
{
  std::array<VertexType, 6 * 6> vertices;
  const float hW = size.x / 2.f;
  const float hH = size.y / 2.f;
  const float hD = size.z / 2.f;
  const float left = center.x - hW;
  const float right = center.x + hW;
  const float top = center.y + hH;
  const float bottom = center.y - hH;
  const float back = center.z - hD;
  const float front = center.z + hD;
  const Vec2 texLeftBot{0.f, 0.f};
  const Vec2 texLeftTop{0.f, 1.f};
  const Vec2 texRightBot{1.f, 0.f};
  const Vec2 texRightTop{1.f, 1.f};

  // Front face
  const Vec3 frontFaceNormal{0.f, 0.f, 1.f};
  priv::setVertex(vertices[0], {left, bottom, front}, frontFaceNormal, texLeftBot);
  priv::setVertex(vertices[1], {right, bottom, front}, frontFaceNormal, texRightBot);
  priv::setVertex(vertices[2], {right, top, front}, frontFaceNormal, texRightTop);
  priv::setVertex(vertices[3], {right, top, front}, frontFaceNormal, texRightTop);
  priv::setVertex(vertices[4], {left, top, front}, frontFaceNormal, texLeftTop);
  priv::setVertex(vertices[5], {left, bottom, front}, frontFaceNormal, texLeftBot);
  // Top face
  const Vec3 topFaceNormal{0.f, 1.f, 0.f};
  priv::setVertex(vertices[6], {left, top, front}, topFaceNormal, texLeftBot);
  priv::setVertex(vertices[7], {right, top, front}, topFaceNormal, texRightBot);
  priv::setVertex(vertices[8], {right, top, back}, topFaceNormal, texRightTop);
  priv::setVertex(vertices[9], {right, top, back}, topFaceNormal, texRightTop);
  priv::setVertex(vertices[10], {left, top, back}, topFaceNormal, texLeftTop);
  priv::setVertex(vertices[11], {left, top, front}, topFaceNormal, texLeftBot);
  // Right face
  const Vec3 rightFaceNormal{1.f, 0.f, 0.f};
  priv::setVertex(vertices[12], {right, top, front}, rightFaceNormal, texLeftTop);
  priv::setVertex(vertices[13], {right, bottom, front}, rightFaceNormal, texLeftBot);
  priv::setVertex(vertices[14], {right, bottom, back}, rightFaceNormal, texRightBot);
  priv::setVertex(vertices[15], {right, bottom, back}, rightFaceNormal, texRightBot);
  priv::setVertex(vertices[16], {right, top, back}, rightFaceNormal, texRightTop);
  priv::setVertex(vertices[17], {right, top, front}, rightFaceNormal, texLeftTop);
  // Back face
  const Vec3 backFaceNormal{-frontFaceNormal};
  priv::setVertex(vertices[18], {left, bottom, back}, backFaceNormal, texRightBot);
  priv::setVertex(vertices[19], {left, top, back}, backFaceNormal, texRightTop);
  priv::setVertex(vertices[20], {right, top, back}, backFaceNormal, texLeftTop);
  priv::setVertex(vertices[21], {right, top, back}, backFaceNormal, texLeftTop);
  priv::setVertex(vertices[22], {right, bottom, back}, backFaceNormal, texLeftBot);
  priv::setVertex(vertices[23], {left, bottom, back}, backFaceNormal, texRightBot);
  // Bottom face
  const Vec3 bottomFaceNormal{-topFaceNormal};
  priv::setVertex(vertices[24], {left, bottom, front}, bottomFaceNormal, texLeftTop);
  priv::setVertex(vertices[25], {left, bottom, back}, bottomFaceNormal, texLeftBot);
  priv::setVertex(vertices[26], {right, bottom, back}, bottomFaceNormal, texRightBot);
  priv::setVertex(vertices[27], {right, bottom, back}, bottomFaceNormal, texRightBot);
  priv::setVertex(vertices[28], {right, bottom, front}, bottomFaceNormal, texRightTop);
  priv::setVertex(vertices[29], {left, bottom, front}, bottomFaceNormal, texLeftTop);
  // Left face
  const Vec3 leftFaceNormal{-rightFaceNormal};
  priv::setVertex(vertices[30], {left, bottom, front}, leftFaceNormal, texRightBot);
  priv::setVertex(vertices[31], {left, top, front}, leftFaceNormal, texRightTop);
  priv::setVertex(vertices[32], {left, top, back}, leftFaceNormal, texLeftTop);
  priv::setVertex(vertices[33], {left, top, back}, leftFaceNormal, texLeftTop);
  priv::setVertex(vertices[34], {left, bottom, back}, leftFaceNormal, texLeftBot);
  priv::setVertex(vertices[35], {left, bottom, front}, leftFaceNormal, texRightBot);
  return vertices;
}
} // namespace geo
} // namespace aw
