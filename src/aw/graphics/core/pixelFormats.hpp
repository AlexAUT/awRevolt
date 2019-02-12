#pragma once

namespace aw
{
enum class PixelFormat
{
  // uint8's
  R8,
  RG16,
  RGB24,
  RGBA32,
  // Floats
  RFloat,
  RGFloat,
  RGBFloat,
  RGBAFloat,
  // ETC2
  RGB_ETC2,
  RGBA1_ETC2,
  RGBA_ETC2,
};

inline unsigned pixelFormatToChannelCount(PixelFormat format);
inline unsigned pixelFormatToPixelSize(PixelFormat format);

inline unsigned pixelFormatToChannelCount(PixelFormat format)
{
  switch (format)
  {
  // uint8's
  case PixelFormat::R8:
    return 1;
  case PixelFormat::RG16:
    return 2;
  case PixelFormat::RGB24:
    return 3;
  case PixelFormat::RGBA32:
    return 4;
  // floats
  case PixelFormat::RFloat:
    return 1;
  case PixelFormat::RGFloat:
    return 2;
  case PixelFormat::RGBFloat:
    return 3;
  case PixelFormat::RGBAFloat:
    return 4;
  // ETC2
  case PixelFormat::RGB_ETC2:
    return 3;
  case PixelFormat::RGBA1_ETC2:
    return 4;
  case PixelFormat::RGBA_ETC2:
    return 4;
  }

  return 0;
}

inline unsigned pixelFormatToPixelSize(PixelFormat format)
{
  auto numChannels = pixelFormatToChannelCount(format);
  switch (format)
  {
  // uint8's
  case PixelFormat::R8:
  case PixelFormat::RG16:
  case PixelFormat::RGB24:
  case PixelFormat::RGBA32:
    return numChannels;
  // floats
  case PixelFormat::RFloat:
  case PixelFormat::RGFloat:
  case PixelFormat::RGBFloat:
  case PixelFormat::RGBAFloat:
    return numChannels * sizeof(float);
  };

  return 0;
}
} // namespace aw
