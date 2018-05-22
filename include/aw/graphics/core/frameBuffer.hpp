#pragma once

#include <aw/graphics/core/texture2D.hpp>

#include <aw/utils/math/vector.hpp>

typedef unsigned GLenum;

namespace aw
{
class FrameBuffer
{
public:
  enum BindType
  {
    READ = 1,
    DRAW = 2,
    READ_AND_DRAW = 3,
  };

public:
  FrameBuffer();
  ~FrameBuffer();

  void create(unsigned width, unsigned height, unsigned depthPrecision, unsigned stencilPrecision);

  void bind(BindType bindType = READ_AND_DRAW) const;
  void unbind() const;

  const Texture2D& getColorTexture() const;
  const Texture2D& getDepthTexture() const;

  unsigned getId() const;

private:
private:
  unsigned mFrameBuffer;
  Vec2u mSize{0, 0};

  Texture2D mColorTexture;
  Texture2D mDepthTexture;
  Texture2D mSTencilTexture;

  mutable bool mViewportCached{false};
  mutable Vec4i mCacheViewportDim;
};

} // namespace aw
