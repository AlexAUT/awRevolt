#include <aw/graphics/core/texture2D.hpp>

#include <aw/graphics/core/image.hpp>

#include <aw/opengl/opengl.hpp>

namespace aw
{
std::tuple<GLenum, GLenum> pixelFormatToOpengl(PixelFormat format);

Texture2D::Texture2D()
{
  glGenTextures(1, &mId);
}

Texture2D::~Texture2D()
{
  glDeleteTextures(1, &mId);
}

void Texture2D::load(const Image& image)
{
  auto pixelFormat = image.getPixelFormat();
  auto [format, dataType] = pixelFormatToOpengl(pixelFormat);
  load(image.getPixels(), image.getWidth(), image.getHeight(), format, format, dataType);
}

void Texture2D::load(const void* data, unsigned width, unsigned height)
{
  load(data, width, height, GL_RGBA, GL_RGBA, GL_UNSIGNED_BYTE);
}
void Texture2D::load(const void* data, unsigned width, unsigned height, GLenum interalFormat, GLenum format,
                     GLenum dataType)
{
  GL_CHECK(glTexImage2D(GL_TEXTURE_2D, 0, interalFormat, width, height, 0, format, dataType, data));
  setMinFilter(MinFilter::LINEAR);
  setMagFilter(MagFilter::LINEAR);
  setWrapMode(WrapMode::REPEAT);
}

void Texture2D::setMinFilter(MinFilter type)
{
  GLenum glType;
  switch (type)
  {
  case MinFilter::LINEAR:
    glType = GL_LINEAR;
    break;
  case MinFilter::LINEAR_MIPMAP_LINEAR:
    glType = GL_LINEAR_MIPMAP_LINEAR;
    break;
  case MinFilter::NEAREST_MIPMAP_NEAREST:
    glType = GL_NEAREST_MIPMAP_NEAREST;
    break;
  case MinFilter::NEAREST_MIPMAP_LINEAR:
    glType = GL_NEAREST_MIPMAP_LINEAR;
    break;
  case MinFilter::NEAREST:
    glType = GL_NEAREST;
    break;
  default:
    glType = GL_NEAREST;
    break;
  }

  GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, glType));
}

void Texture2D::setMagFilter(MagFilter type)
{
  GLenum glType;
  switch (type)
  {
  case MagFilter::LINEAR:
    glType = GL_LINEAR;
    break;
  case MagFilter::NEAREST:
    glType = GL_NEAREST;
    break;
  default:
    glType = GL_NEAREST;
    break;
  }
  GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, glType));
}

GLenum wrapModeToGLType(Texture2D::WrapMode mode)
{
  switch (mode)
  {
  case Texture2D::WrapMode::REPEAT:
    return GL_REPEAT;
  case Texture2D::WrapMode::CLAMP_TO_EDGE:
    return GL_CLAMP_TO_EDGE;
  case Texture2D::WrapMode::MIRRORED_REPEAT:
    return GL_MIRRORED_REPEAT;
  case Texture2D::WrapMode::CLAMP_TO_BORDER:
#ifdef GL_CLAMP_TO_BORDER
    return GL_CLAMP_TO_BORDER;
#else
    return GL_CLAMP_TO_EDGE;
#endif
  default:
    return GL_REPEAT;
  }
}

void Texture2D::setWrapMode(WrapMode mode)
{
  setWrapModeS(mode);
  setWrapModeT(mode);
}

void Texture2D::setWrapModeS(WrapMode mode)
{
  auto glType = wrapModeToGLType(mode);
  GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, glType));
}

void Texture2D::setWrapModeT(WrapMode mode)
{
  auto glType = wrapModeToGLType(mode);
  GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, glType));
}

void Texture2D::bind(unsigned int textureUnit) const
{
  GL_CHECK(glActiveTexture(GL_TEXTURE0 + textureUnit));
  GL_CHECK(glBindTexture(GL_TEXTURE_2D, mId));
  mBoundTextureUnit = textureUnit;
}

void Texture2D::unbind() const
{
  GL_CHECK(glActiveTexture(GL_TEXTURE0 + mBoundTextureUnit));
  GL_CHECK(glBindTexture(GL_TEXTURE_2D, 0));
}

unsigned Texture2D::getId() const
{
  return mId;
}

std::tuple<GLenum, GLenum> pixelFormatToOpengl(PixelFormat format)
{
  switch (format)
  {
  // uint8's
  case PixelFormat::R8:
    return {GL_R8, GL_UNSIGNED_BYTE};
  case PixelFormat::RG8:
    return {GL_RG8, GL_UNSIGNED_BYTE};
  case PixelFormat::RGB8:
    return {GL_RGB8, GL_UNSIGNED_BYTE};
  case PixelFormat::RGBA8:
    return {GL_RGBA8, GL_UNSIGNED_BYTE};
  // float
  case PixelFormat::RFloat:
    return {GL_R32F, GL_FLOAT};
  case PixelFormat::RGFloat:
    return {GL_RG32F, GL_FLOAT};
  case PixelFormat::RGBFloat:
    return {GL_RGB32F, GL_FLOAT};
  case PixelFormat::RGBAFloat:
    return {GL_RGBA32F, GL_FLOAT};
  // etc2
  case PixelFormat::RGB_ETC2:
    return {GL_COMPRESSED_RGB8_ETC2, GL_UNSIGNED_BYTE};
  case PixelFormat::RGBA_ETC2:
    return {GL_COMPRESSED_RGBA8_ETC2_EAC, GL_UNSIGNED_BYTE};
  case PixelFormat::RGBA1_ETC2:
    return {GL_COMPRESSED_RGB8_PUNCHTHROUGH_ALPHA1_ETC2, GL_UNSIGNED_BYTE};
  }
  return {GL_NONE, GL_NONE};
}
} // namespace aw
