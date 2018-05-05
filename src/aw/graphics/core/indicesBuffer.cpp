#include <aw/graphics/core/indicesBuffer.hpp>

#include <aw/opengl/opengl.hpp>

namespace aw
{
IndicesBuffer::IndicesBuffer() : BufferObject(GL_ARRAY_BUFFER)
{
}

IndicesBuffer::IndicesBuffer(GLbitfield usage) : BufferObject(GL_ARRAY_BUFFER, usage)
{
}

} // namespace aw
