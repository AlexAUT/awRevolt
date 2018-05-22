#include <aw/graphics/core/renderBuffer.hpp>

#include <aw/opengl/opengl.hpp>

namespace aw
{
RenderBuffer::RenderBuffer()
{
  glGenRenderbuffers(1, &mRenderBuffer);
}
RenderBuffer::~RenderBuffer()
{
  glDeleteRenderbuffers(1, &mRenderBuffer);
}

void RenderBuffer::create(unsigned width, unsigned height)
{
  create(width, height, 0);
}

void RenderBuffer::create(unsigned width, unsigned height, GLenum type)
{
  bind();
  GL_CHECK(glRenderbufferStorage(GL_RENDERBUFFER, type, width, height));
}

void RenderBuffer::bind() const
{
  GL_CHECK(glBindRenderbuffer(GL_RENDERBUFFER, mRenderBuffer));
}

void RenderBuffer::unbind() const
{
  GL_CHECK(glBindRenderbuffer(GL_RENDERBUFFER, 0));
}

} // namespace aw
