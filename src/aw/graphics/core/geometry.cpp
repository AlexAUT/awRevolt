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

std::array<Vertex, 6 * 6> cube(Vec3 center, Vec3 size)
{
  std::array<Vertex, 6 * 6> vertices;
  const float hW = size.x / 2.f;
  const float hH = size.y / 2.f;
  const float hD = size.z / 2.f;
  const float left = center.x - hW;
  const float right = center.x + hW;
  const float top = center.y + hH;
  const float bottom = center.y - hW;
  const float back = center.z - hD;
  const float front = center.z + hD;
  const Vec2 texLeftBot{0.f, 0.f};
  const Vec2 texLeftTop{0.f, 1.f};
  const Vec2 texRightBot{1.f, 0.f};
  const Vec2 texRightTop{1.f, 1.f};

  // Front face
  const Vec3 frontFaceNormal{0.f, 0.f, 1.f};
  vertices[0] = {{left, bottom, front}, frontFaceNormal, texLeftBot};
  vertices[1] = {{right, bottom, front}, frontFaceNormal, texRightBot};
  vertices[2] = {{right, top, front}, frontFaceNormal, texRightTop};
  vertices[3] = {{right, top, front}, frontFaceNormal, texRightTop};
  vertices[4] = {{left, top, front}, frontFaceNormal, texLeftTop};
  vertices[5] = {{left, bottom, front}, frontFaceNormal, texLeftBot};
  // Top face
  const Vec3 topFaceNormal{0.f, 1.f, 0.f};
  vertices[6] = {{left, top, front}, topFaceNormal, texLeftBot};
  vertices[7] = {{right, top, front}, topFaceNormal, texRightBot};
  vertices[8] = {{right, top, back}, topFaceNormal, texRightTop};
  vertices[9] = {{right, top, back}, topFaceNormal, texRightTop};
  vertices[10] = {{left, top, back}, topFaceNormal, texLeftTop};
  vertices[11] = {{left, top, front}, topFaceNormal, texLeftBot};
  // Right face
  const Vec3 rightFaceNormal{1.f, 0.f, 0.f};
  vertices[12] = {{right, top, front}, rightFaceNormal, texLeftTop};
  vertices[13] = {{right, bottom, front}, rightFaceNormal, texLeftBot};
  vertices[14] = {{right, bottom, back}, rightFaceNormal, texRightBot};
  vertices[15] = {{right, bottom, back}, rightFaceNormal, texRightBot};
  vertices[16] = {{right, top, back}, rightFaceNormal, texRightTop};
  vertices[17] = {{right, top, front}, rightFaceNormal, texLeftTop};
  // Back face
  const Vec3 backFaceNormal{-frontFaceNormal};
  vertices[18] = {{left, bottom, back}, backFaceNormal, texRightBot};
  vertices[19] = {{left, top, back}, backFaceNormal, texRightTop};
  vertices[20] = {{right, top, back}, backFaceNormal, texLeftTop};
  vertices[21] = {{right, top, back}, backFaceNormal, texLeftTop};
  vertices[22] = {{right, bottom, back}, backFaceNormal, texLeftBot};
  vertices[23] = {{left, bottom, back}, backFaceNormal, texRightBot};
  // Bottom face
  const Vec3 bottomFaceNormal{-topFaceNormal};
  vertices[24] = {{left, bottom, front}, bottomFaceNormal, texLeftTop};
  vertices[25] = {{left, bottom, back}, bottomFaceNormal, texLeftBot};
  vertices[26] = {{right, bottom, back}, bottomFaceNormal, texRightBot};
  vertices[27] = {{right, bottom, back}, bottomFaceNormal, texRightBot};
  vertices[28] = {{right, bottom, front}, bottomFaceNormal, texRightTop};
  vertices[29] = {{left, bottom, front}, bottomFaceNormal, texLeftTop};
  // Left face
  const Vec3 leftFaceNormal{-rightFaceNormal};
  vertices[30] = {{left, bottom, front}, leftFaceNormal, texRightBot};
  vertices[31] = {{left, top, front}, leftFaceNormal, texRightTop};
  vertices[32] = {{left, top, back}, leftFaceNormal, texLeftTop};
  vertices[33] = {{left, top, back}, leftFaceNormal, texLeftTop};
  vertices[34] = {{left, bottom, back}, leftFaceNormal, texLeftBot};
  vertices[35] = {{left, bottom, front}, leftFaceNormal, texRightBot};
  return vertices;
}

std::array<Vertex, 8 * 3> octahedron(Vec3 center, float radius){

};
} // namespace geo
} // namespace aw
