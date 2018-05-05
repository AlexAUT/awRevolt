#pragma once

#include <aw/graphics/core/bufferObject.hpp>

namespace aw
{
class IndicesBuffer : public BufferObject
{
public:
  IndicesBuffer();
  IndicesBuffer(GLbitfield usage);
};
} // namespace aw
