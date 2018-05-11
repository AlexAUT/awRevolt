#pragma once

#include <aw/graphics/core/color.hpp>
#include <aw/graphics/core/vertexLayout.hpp>
#include <aw/utils/math/vector.hpp>

namespace aw
{

struct Vertex
{
  Vec3 position;
  Vec3 normal;
  Vec2 texCoord;

  static VertexLayout<3> Layout;
};

struct VertexPosNormalColor
{
  Vec3 position;
  Vec3 normal;
  Color color;

  static VertexLayout<3> Layout;
};

struct VertexPosTex
{
  Vec3 position;
  Vec2 texCoord;

  static VertexLayout<2> Layout;
};

struct VertexPosColor
{
  Vec3 position;
  Vec4 color;
  static VertexLayout<2> Layout;
};

struct VertexBones
{
  Vec3 position;
  Vec3 normal;
  Vec2 texCoord;
  Vec4 boneIds;
  Vec4 boneWeights;

  static VertexLayout<5> Layout;
};

} // namespace aw
