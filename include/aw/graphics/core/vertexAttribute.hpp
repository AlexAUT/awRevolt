#pragma once

#include <aw/graphics/core/bufferObject.hpp>

namespace aw
{
typedef unsigned GLenum;

struct VertexAttribute
{
  BufferObject* buffer;
  int index;
  int size;
  GLenum type;
  GLenum normalized;
  int stride;
  void* offset;
};

} // namespace aw
