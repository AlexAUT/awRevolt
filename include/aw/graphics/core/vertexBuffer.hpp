#pragma once

#include <aw/graphics/core/bufferObject.hpp>

namespace aw
{
class VertexBuffer : public BufferObject
{
public:
  VertexBuffer();
  VertexBuffer(GLbitfield usage);
};
} // namespace aw
