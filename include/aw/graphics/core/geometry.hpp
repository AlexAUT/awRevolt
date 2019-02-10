#pragma once

#include <aw/graphics/core/vertex.hpp>
#include <aw/utils/math/constants.hpp>
#include <aw/utils/math/rect.hpp>
#include <aw/utils/math/vector.hpp>
#include <aw/utils/spatial/AABB.hpp>

#include <array>
#include <cmath>
#include <vector>

namespace aw
{
namespace geo
{
template <typename VertexIterator>
VertexIterator line(Vec3 from, Vec3 to, VertexIterator insertIterator);

size_t lineGridVertexCount(Vec2 size, Vec2 cellSize);
template <typename VertexIterator>
VertexIterator lineGrid(Vec3 center, Vec2 size, Vec2 cellSize, VertexIterator insertIterator);

std::array<Vertex, 6> quad(float left, float bottom, float width, float height, float depth = 0.f);
std::array<Vertex, 6> quad(float left, float bottom, float width, float height, RectFloat texCoords, float depth = 0.f);
std::array<Vertex, 6> quad(RectFloat rect, float depth = 0.f);
std::array<Vertex, 6> quad(RectFloat rect, RectFloat texCoords, float depth = 0.f);

template <std::size_t vertexCount>
std::array<float, (vertexCount + 2) * 3> circle(float centerX, float centerY, float radius, float depth = 0.f);

template <typename VertexType>
std::array<VertexType, 6 * 6> cube(Vec3 center, Vec3 size);

template <typename VertexIterator>
void cube(Vec3 center, Vec3 size, VertexIterator begin);

template <typename VertexType>
std::array<VertexType, 6 * 6> cube(AABB aabb)
{
  return cube<VertexType>(aabb.getCenter(), aabb.getSize());
}

template <typename VertexIterator>
void cube(AABB aabb, VertexIterator begin)
{
  return cube(aabb.getCenter(), aabb.getSize(), begin);
}

template <typename VertexIterator>
void cubePoints(Vec3 center, Vec3 size, VertexIterator begin);

template <typename VertexIterator>
void cubeLines(Vec3 center, Vec3 size, VertexIterator begin);

// Make it quadratic, to calculate normals more easily (use scale afterwards to
// create non quadratic)
std::array<Vertex, 8 * 3> octahedron(Vec3 center, float radius);
} // namespace geo

} // namespace aw

#include <aw/graphics/core/geometry.inl>
