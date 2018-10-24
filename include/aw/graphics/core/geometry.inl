#pragma once

#include <aw/graphics/core/geometry.hpp>

#include <aw/utils/log.hpp>
#include <aw/utils/typeHelper/typeChecks.hpp>

#include <algorithm>
#include <type_traits>

namespace aw
{
namespace geo
{
namespace priv
{
MEMBER_PRESENT_CHECKER(position, Vec3)
MEMBER_PRESENT_CHECKER(normal, Vec3)
MEMBER_PRESENT_CHECKER(texCoord, Vec2)

template <typename VertexIterator>
void setVertex(VertexIterator vertexIterator, Vec3 pos, Vec3 normal, Vec2 texCoord)
{
  using VertexType = typename std::decay<decltype(*vertexIterator)>::type;

  if constexpr (Has_position<VertexType>{})
    (*vertexIterator).position = pos;
  if constexpr (Has_normal<VertexType>{})
    (*vertexIterator).normal = normal;
  if constexpr (Has_texCoord<VertexType>{})
    (*vertexIterator).texCoord = texCoord;
}
} // namespace priv

template <typename VertexType>
std::array<VertexType, 6 * 6> cube(Vec3 center, Vec3 size)
{
  std::array<VertexType, 6 * 6> result;
  cube(center, size, result.begin());
  return result;
}

template <typename VertexIterator>
void cube(Vec3 center, Vec3 size, VertexIterator begin)
{
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
  priv::setVertex(begin++, {left, bottom, front}, frontFaceNormal, texLeftBot);
  priv::setVertex(begin++, {right, bottom, front}, frontFaceNormal, texRightBot);
  priv::setVertex(begin++, {right, top, front}, frontFaceNormal, texRightTop);
  priv::setVertex(begin++, {right, top, front}, frontFaceNormal, texRightTop);
  priv::setVertex(begin++, {left, top, front}, frontFaceNormal, texLeftTop);
  priv::setVertex(begin++, {left, bottom, front}, frontFaceNormal, texLeftBot);
  // Top face
  const Vec3 topFaceNormal{0.f, 1.f, 0.f};
  priv::setVertex(begin++, {left, top, front}, topFaceNormal, texLeftBot);
  priv::setVertex(begin++, {right, top, front}, topFaceNormal, texRightBot);
  priv::setVertex(begin++, {right, top, back}, topFaceNormal, texRightTop);
  priv::setVertex(begin++, {right, top, back}, topFaceNormal, texRightTop);
  priv::setVertex(begin++, {left, top, back}, topFaceNormal, texLeftTop);
  priv::setVertex(begin++, {left, top, front}, topFaceNormal, texLeftBot);
  // Right face
  const Vec3 rightFaceNormal{1.f, 0.f, 0.f};
  priv::setVertex(begin++, {right, top, front}, rightFaceNormal, texLeftTop);
  priv::setVertex(begin++, {right, bottom, front}, rightFaceNormal, texLeftBot);
  priv::setVertex(begin++, {right, bottom, back}, rightFaceNormal, texRightBot);
  priv::setVertex(begin++, {right, bottom, back}, rightFaceNormal, texRightBot);
  priv::setVertex(begin++, {right, top, back}, rightFaceNormal, texRightTop);
  priv::setVertex(begin++, {right, top, front}, rightFaceNormal, texLeftTop);
  // Back face
  const Vec3 backFaceNormal{-frontFaceNormal};
  priv::setVertex(begin++, {left, bottom, back}, backFaceNormal, texRightBot);
  priv::setVertex(begin++, {left, top, back}, backFaceNormal, texRightTop);
  priv::setVertex(begin++, {right, top, back}, backFaceNormal, texLeftTop);
  priv::setVertex(begin++, {right, top, back}, backFaceNormal, texLeftTop);
  priv::setVertex(begin++, {right, bottom, back}, backFaceNormal, texLeftBot);
  priv::setVertex(begin++, {left, bottom, back}, backFaceNormal, texRightBot);
  // Bottom face
  const Vec3 bottomFaceNormal{-topFaceNormal};
  priv::setVertex(begin++, {left, bottom, front}, bottomFaceNormal, texLeftTop);
  priv::setVertex(begin++, {left, bottom, back}, bottomFaceNormal, texLeftBot);
  priv::setVertex(begin++, {right, bottom, back}, bottomFaceNormal, texRightBot);
  priv::setVertex(begin++, {right, bottom, back}, bottomFaceNormal, texRightBot);
  priv::setVertex(begin++, {right, bottom, front}, bottomFaceNormal, texRightTop);
  priv::setVertex(begin++, {left, bottom, front}, bottomFaceNormal, texLeftTop);
  // Left face
  const Vec3 leftFaceNormal{-rightFaceNormal};
  priv::setVertex(begin++, {left, bottom, front}, leftFaceNormal, texRightBot);
  priv::setVertex(begin++, {left, top, front}, leftFaceNormal, texRightTop);
  priv::setVertex(begin++, {left, top, back}, leftFaceNormal, texLeftTop);
  priv::setVertex(begin++, {left, top, back}, leftFaceNormal, texLeftTop);
  priv::setVertex(begin++, {left, bottom, back}, leftFaceNormal, texLeftBot);
  priv::setVertex(begin++, {left, bottom, front}, leftFaceNormal, texRightBot);
}

template <typename VertexIterator>
void cubePoints(Vec3 center, Vec3 size, VertexIterator begin)
{
  const float hW = size.x / 2.f;
  const float hH = size.y / 2.f;
  const float hD = size.z / 2.f;
  const float left = center.x - hW;
  const float right = center.x + hW;
  const float top = center.y + hH;
  const float bottom = center.y - hH;
  const float back = center.z - hD;
  const float front = center.z + hD;

  const Vec3 null{0.f, 0.f, 0.f};
  // Front face points
  priv::setVertex(begin++, {left, bottom, front}, null, null);
  priv::setVertex(begin++, {right, bottom, front}, null, null);
  priv::setVertex(begin++, {left, top, front}, null, null);
  priv::setVertex(begin++, {right, top, front}, null, null);
  // Back face points
  priv::setVertex(begin++, {left, bottom, back}, null, null);
  priv::setVertex(begin++, {right, bottom, back}, null, null);
  priv::setVertex(begin++, {left, top, back}, null, null);
  priv::setVertex(begin++, {right, top, back}, null, null);
}

template <typename VertexIterator>
void cubeLines(Vec3 center, Vec3 size, VertexIterator begin)
{
  const float hW = size.x / 2.f;
  const float hH = size.y / 2.f;
  const float hD = size.z / 2.f;
  const float left = center.x - hW;
  const float right = center.x + hW;
  const float top = center.y + hH;
  const float bottom = center.y - hH;
  const float back = center.z - hD;
  const float front = center.z + hD;

  const Vec3 null{0.f, 0.f, 0.f};
  // Front face lines
  priv::setVertex(begin++, {left, bottom, front}, null, null);
  priv::setVertex(begin++, {right, bottom, front}, null, null);
  priv::setVertex(begin++, {right, bottom, front}, null, null);
  priv::setVertex(begin++, {right, top, front}, null, null);
  priv::setVertex(begin++, {right, top, front}, null, null);
  priv::setVertex(begin++, {left, top, front}, null, null);
  priv::setVertex(begin++, {left, top, front}, null, null);
  priv::setVertex(begin++, {left, bottom, front}, null, null);
  // Back face lines
  priv::setVertex(begin++, {left, bottom, back}, null, null);
  priv::setVertex(begin++, {right, bottom, back}, null, null);
  priv::setVertex(begin++, {right, bottom, back}, null, null);
  priv::setVertex(begin++, {right, top, back}, null, null);
  priv::setVertex(begin++, {right, top, back}, null, null);
  priv::setVertex(begin++, {left, top, back}, null, null);
  priv::setVertex(begin++, {left, top, back}, null, null);
  priv::setVertex(begin++, {left, bottom, back}, null, null);
  // Connecting front and back faces
  priv::setVertex(begin++, {left, bottom, back}, null, null);
  priv::setVertex(begin++, {left, bottom, front}, null, null);
  priv::setVertex(begin++, {right, bottom, back}, null, null);
  priv::setVertex(begin++, {right, bottom, front}, null, null);
  priv::setVertex(begin++, {right, top, back}, null, null);
  priv::setVertex(begin++, {right, top, front}, null, null);
  priv::setVertex(begin++, {left, top, back}, null, null);
  priv::setVertex(begin++, {left, top, front}, null, null);
}
} // namespace geo
} // namespace aw
