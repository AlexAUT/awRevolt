#pragma once

#include <aw/graphics/core/pixelFormats.hpp>
#include <aw/utils/math/vector.hpp>

typedef unsigned GLenum;

namespace aw
{
class Image;

class Texture2D
{
public:
  enum class MinFilter
  {
    NEAREST,
    LINEAR,
    NEAREST_MIPMAP_NEAREST,
    NEAREST_MIPMAP_LINEAR,
    LINEAR_MIPMAP_LINEAR,
  };
  enum class MagFilter
  {
    NEAREST,
    LINEAR,
  };
  enum class WrapMode
  {
    CLAMP_TO_EDGE,
    CLAMP_TO_BORDER,
    MIRRORED_REPEAT,
    REPEAT,
  };
  Texture2D();
  ~Texture2D();

  void load(const Image& img);
  void load(const void* data, unsigned width, unsigned height, PixelFormat pixelFormat);
  void loadCompressed(const void* data, PixelFormat format);

  void bind(unsigned textureUnit = 0) const;
  void unbind() const;

  void setMinFilter(MinFilter type);
  void setMagFilter(MagFilter type);
  void setWrapMode(WrapMode mode);
  void setWrapModeS(WrapMode mode);
  void setWrapModeT(WrapMode mode);

  unsigned getId() const;
  Vec2u getSize() const { return mSize; }
  PixelFormat getPixelFormat() const { return mPixelFormat; }

private:
private:
  unsigned mId;

  Vec2u mSize;
  PixelFormat mPixelFormat;

  // Used to unbind the correct texture unit
  mutable unsigned mBoundTextureUnit;
};

} // namespace aw
