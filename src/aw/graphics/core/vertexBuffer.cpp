#include <aw/graphics/core/vertexBuffer.hpp>

#include <aw/opengl/opengl.hpp>

namespace aw
{
VertexBuffer::VertexBuffer() : BufferObject(GL_ARRAY_BUFFER)
{
}

VertexBuffer::VertexBuffer(GLbitfield usage) : BufferObject(GL_ARRAY_BUFFER, usage)
{
}

} // namespace aw
