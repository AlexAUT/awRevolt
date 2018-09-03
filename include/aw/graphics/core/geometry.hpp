#pragma once

#include <aw/graphics/core/vertex.hpp>
#include <aw/utils/math/constants.hpp>
#include <aw/utils/math/vector.hpp>
#include <aw/utils/rect.hpp>

#include <array>
#include <cmath>

namespace aw
{
namespace geo
{

template <typename VertexType>
std::array<VertexType, 2> line(Vec3 from, Vec3 to);
template <typename VertexType>
std::array<VertexType, 2> line(Vec3 from, Vec3 to, VertexType templateVertex);

std::array<Vertex, 6> quad(float left, float bottom, float width, float height, float depth = 0.f);
std::array<Vertex, 6> quad(float left, float bottom, float width, float height, RectFloat texCoords, float depth = 0.f);
std::array<Vertex, 6> quad(RectFloat rect, float depth = 0.f);
std::array<Vertex, 6> quad(RectFloat rect, RectFloat texCoords, float depth = 0.f);

template <std::size_t vertexCount>
std::array<float, (vertexCount + 2) * 3> circle(float centerX, float centerY, float radius, float depth = 0.f);

template <typename VertexType>
std::array<VertexType, 6 * 6> cube(Vec3 center, Vec3 size);
// Make it quadratic, to calculate normals more easily (use scale afterwards to
// create non quadratic)
std::array<Vertex, 8 * 3> octahedron(Vec3 center, float radius);
} // namespace geo

// Implementation of inline functions
namespace geo
{
template <std::size_t vertexCount>
std::array<float, (vertexCount + 2) * 3> circle(float centerX, float centerY, float radius, float depth)
{
  std::array<float, (vertexCount + 2) * 3> result;
  result[0] = centerX;
  result[1] = centerY;
  result[2] = depth;
  constexpr float pi2 = 2 * constantsF::PI;
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

template <typename VertexType>
std::array<VertexType, 2> line(Vec3 from, Vec3 to)
{
  std::array<VertexType, 2> vertices;
  vertices[0].position = from;
  vertices[1].position = to;
  return vertices;
}

template <typename VertexType>
std::array<VertexType, 2> line(Vec3 from, Vec3 to, VertexType templateVertex)
{
  std::array<VertexType, 2> vertices{templateVertex, templateVertex};
  vertices[0].position = from;
  vertices[1].position = to;

  return vertices;
}

} // namespace geo

} // namespace aw

#include <aw/graphics/core/geometry.inl>
