#pragma once

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
  void load(const void* data, unsigned width, unsigned height);
  void load(const void* data, unsigned width, unsigned height, GLenum interalFormat, GLenum format, GLenum dataType);

  void bind(unsigned textureUnit = 0) const;
  void unbind() const;

  void setMinFilter(MinFilter type);
  void setMagFilter(MagFilter type);
  void setWrapMode(WrapMode mode);
  void setWrapModeS(WrapMode mode);
  void setWrapModeT(WrapMode mode);

  unsigned getId() const;

private:
private:
  unsigned mId;

  // Used to unbind the correct texture unit
  mutable unsigned mBoundTextureUnit;
};

} // namespace aw
