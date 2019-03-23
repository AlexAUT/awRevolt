#include <aw/graphics/core/frameBuffer.hpp>

#include <aw/config.hpp>

#include <aw/opengl/opengl.hpp>
#include <aw/opengl/openglExt.hpp>
#include <aw/utils/log.hpp>

#include <cstring>

namespace aw
{
FrameBuffer::FrameBuffer()
{
  GL_CHECK(glGenFramebuffers(1, &mFrameBuffer));
}

FrameBuffer::~FrameBuffer()
{
  GL_CHECK(glDeleteBuffers(1, &mFrameBuffer));
}

void FrameBuffer::create(unsigned width, unsigned height, unsigned depthPrecision, unsigned stencilPrecision)
{
  mSize = {width, height};
  bind();

  mColorTexture.bind();
  mColorTexture.load(nullptr, width, height, PixelFormat::RGB8);
  mColorTexture.setMagFilter(Texture2D::MagFilter::NEAREST);
  GL_CHECK(glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, mColorTexture.getId(), 0));

  if (depthPrecision > 0)
  {
    mDepthTexture.bind();

    mDepthTexture.load(nullptr, width, height, PixelFormat::Depth16);

    mDepthTexture.setMagFilter(Texture2D::MagFilter::LINEAR);
    mDepthTexture.setMinFilter(Texture2D::MinFilter::LINEAR);
    mDepthTexture.setWrapMode(Texture2D::WrapMode::CLAMP_TO_BORDER);
    GL_CHECK(glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, mDepthTexture.getId(), 0));
  }
  if (stencilPrecision > 0)
  {
    throw std::runtime_error("Stencil buffers not implemented!");
  }

#ifdef AW_DESKTOP
  GLenum drawBuffers[1] = {GL_COLOR_ATTACHMENT0};
  GL_CHECK(glDrawBuffers(1, drawBuffers));
#endif
  if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
  {
    throw std::runtime_error("Framebuffer could not be created!");
  }

  unbind();
}

void FrameBuffer::bind(BindType bindType) const
{
  GLenum bindTarget = GL_FRAMEBUFFER;
#ifdef AW_DESKTOP
  if (bindType == READ_AND_DRAW)
    bindTarget = GL_FRAMEBUFFER;
  else if (bindType == READ)
    bindTarget = GL_READ_FRAMEBUFFER;
  else if (bindType == DRAW)
    bindTarget = GL_DRAW_FRAMEBUFFER;
#endif

  GL_CHECK(glGetIntegerv(GL_VIEWPORT, &mCacheViewportDim.x));
  mViewportCached = true;
  GL_CHECK(glViewport(0, 0, mSize.x, mSize.y));
  GL_CHECK(glBindFramebuffer(bindTarget, mFrameBuffer));
}

void FrameBuffer::unbind() const
{
  if (mViewportCached)
  {
    mViewportCached = false;
    GL_CHECK(glViewport(mCacheViewportDim.x, mCacheViewportDim.y, mCacheViewportDim.z, mCacheViewportDim.w));
  }
  GL_CHECK(glBindFramebuffer(GL_FRAMEBUFFER, 0));
}

const Texture2D& FrameBuffer::getColorTexture() const
{
  return mColorTexture;
}

const Texture2D& FrameBuffer::getDepthTexture() const
{
  return mDepthTexture;
}

unsigned FrameBuffer::getId() const
{
  return mFrameBuffer;
}

} // namespace aw
