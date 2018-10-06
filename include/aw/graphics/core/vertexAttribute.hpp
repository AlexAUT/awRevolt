#pragma once

#include <aw/graphics/core/bufferObject.hpp>

namespace aw
{
typedef unsigned GLenum;
typedef unsigned char GLboolean;

struct VertexAttribute
{
  int index;
  int size;
  GLenum type;
  GLboolean normalized;
  int stride;
  const void* offset;
};

} // namespace aw
