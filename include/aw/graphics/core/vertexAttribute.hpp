#pragma once

#include <aw/graphics/core/bufferObject.hpp>

namespace aw
{
typedef unsigned GLenum;

struct VertexAttribute
{
  int index;
  int size;
  GLenum type;
  GLenum normalized;
  int stride;
  const void* offset;
};

} // namespace aw
