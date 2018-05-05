#include <aw/graphics/core/bufferObject.hpp>

#include <aw/opengl/opengl.hpp>

namespace aw
{
BufferObject::BufferObject(GLenum type) : BufferObject(type, GL_STATIC_DRAW)
{
  GL_CHECK(glGenBuffers(1, &mId));
}

BufferObject::BufferObject(GLenum type, GLbitfield usage) : mType(type), mUsage(usage)
{
  GL_CHECK(glGenBuffers(1, &mId));
}

BufferObject::~BufferObject()
{
  GL_CHECK(glDeleteBuffers(1, &mId));
}

void BufferObject::setData(const void* data, unsigned size)
{
  GL_CHECK(glBufferData(mType, size, data, mUsage));
}

void BufferObject::setSubData(void* data, unsigned size, ptrdiff offset)
{
  GL_CHECK(glBufferSubData(mType, offset, size, data));
}

void BufferObject::bind() const
{
  GL_CHECK(glBindBuffer(mType, mId));
}

void BufferObject::unbind() const
{
  GL_CHECK(glBindBuffer(mType, 0));
}

} // namespace aw
