#pragma once

#include <aw/graphics/core/geometry.hpp>

#include <aw/utils/typeHelper/typeChecks.hpp>

#include <algorithm>
#include <type_traits>

namespace aw::geo
{
namespace priv
{
MEMBER_PRESENT_CHECKER(position, Vec3)
MEMBER_PRESENT_CHECKER(normal, Vec3)
MEMBER_PRESENT_CHECKER(texCoord, Vec2)

template <typename VertexIterator>
void setVertex(VertexIterator vertexIterator, Vec3 pos, Vec3 normal = Vec3{0.f}, Vec2 texCoord = Vec2{0.f})
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

template <std::size_t vertexCount>
std::array<float, (vertexCount + 2) * 3> circle(float centerX, float centerY, float radius, float depth)
{
  std::array<float, (vertexCount + 2) * 3> result;
  result[0] = centerX;
  result[1] = centerY;
  result[2] = depth;
  constexpr float pi2 = 2 * aw::constants::pi();
  constexpr float oneIter = pi2 / vertexCount;
  float angle = 0;
  for (std::size_t i = 1; i < vertexCount + 2; i++)
  {
    result[i * 3] = centerX + std::cos(angle) * radius;
    result[i * 3 + 1] = centerY + std::sin(angle) * radius;
    result[i * 3 + 2] = depth;
    angle += oneIter;
  }
  return result;
}

template <typename VertexIterator>
VertexIterator line(Vec3 from, Vec3 to, VertexIterator insertIterator)
{
  priv::setVertex(insertIterator++, from);
  priv::setVertex(insertIterator++, to);
  return insertIterator;
}

template <typename VertexIterator>
VertexIterator lineGrid(Vec3 center, Vec2 size, Vec2 cellSize, VertexIterator insertIterator)
{
  auto sizeHalf = size * 0.5f;
  auto leftTop = center - Vec3{sizeHalf.x, 0, sizeHalf.y};
  if (size.y >= cellSize.y)
  {
    for (float z = 0; z <= size.y; z += cellSize.y)
    {
      Vec3 from{center.x + sizeHalf.x, 0, leftTop.z + z};
      Vec3 to{center.x - sizeHalf.x, 0, from.z};
      insertIterator = line(from, to, insertIterator);
    }
  }
  if (size.x >= cellSize.x)
  {
    for (float x = 0; x <= size.x; x += cellSize.x)
    {
      Vec3 from{leftTop.x + x, 0, center.z + sizeHalf.y};
      Vec3 to{from.x, 0, center.z - sizeHalf.y};
      insertIterator = line(from, to, insertIterator);
    }
  }
  return insertIterator;
}

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
} // namespace aw::geo
