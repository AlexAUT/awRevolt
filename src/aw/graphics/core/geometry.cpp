#include <aw/graphics/core/geometry.hpp>

#include <aw/utils/rect.hpp>

#include <glm/geometric.hpp>

namespace aw
{
namespace geo
{

std::array<Vertex, 6> quad(float left, float bottom, float width, float height, float depth)
{
  RectFloat texCoords{0.f, 0.f, 1.f, 1.f};
  return quad(left, bottom, width, height, texCoords, depth);
}

std::array<Vertex, 6> quad(float left, float bottom, float width, float height, RectFloat texCoords, float depth)
{
  Vec3 normal{0.f, 0.f, 1.f};
  const auto& tC = texCoords;
  return {
      Vertex{{left, bottom, depth}, {normal.x, normal.y, normal.z}, {tC.left, tC.bottom}}, // Bottom left
      Vertex{{left + width, bottom, depth},
             {normal.x, normal.y, normal.z},
             {tC.left + tC.width, tC.bottom}}, // Bottom right
      Vertex{
          {left, bottom + height, depth}, {normal.x, normal.y, normal.z}, {tC.left, tC.bottom + tC.height}}, // Top left
      Vertex{
          {left, bottom + height, depth}, {normal.x, normal.y, normal.z}, {tC.left, tC.bottom + tC.height}}, // Top left
      Vertex{{left + width, bottom, depth},
             {normal.x, normal.y, normal.z},
             {tC.left + tC.width, tC.bottom}}, // Bottom right
      Vertex{{left + width, bottom + height, depth},
             {normal.x, normal.y, normal.z},
             {tC.left + tC.width, tC.bottom + tC.height}}, // Top right
  };
}

std::array<Vertex, 6> quad(RectFloat rect, float depth)
{
  return quad(rect.left, rect.bottom, rect.width, rect.height, depth);
}

std::array<Vertex, 6> quad(RectFloat rect, RectFloat texCoords, float depth)
{
  return quad(rect.left, rect.bottom, rect.width, rect.height, texCoords, depth);
}

std::array<Vertex, 8 * 3> octahedron(Vec3 center, float radius)
{
  (void)center;
  (void)radius;
  return {};
}
} // namespace geo
} // namespace aw
