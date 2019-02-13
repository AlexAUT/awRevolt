#pragma once

#include <aw/graphics/core/pixelFormats.hpp>
#include <aw/utils/types.hpp>

#include <istream>
#include <memory>
#include <string>

namespace aw
{
class Path;

class Image
{
public:
  static Image convertToPixelFormat(const Image& image, PixelFormat newFormat);

public:
  Image() = default;
  Image(PixelFormat format, unsigned width, unsigned height, std::unique_ptr<uint8> data = nullptr);

  bool load(const aw::Path& path);

  // This does invalidate the content of the image
  void resize(unsigned width, unsigned height);
  // This does invalidate the content of the image
  void setPixelFormat(PixelFormat pixelFormat);

  unsigned getWidth() const { return mWidth; }
  unsigned getHeight() const { return mHeight; }
  unsigned getChannelCount() const { return pixelFormatToChannelCount(mPixelFormat); }

  // The default interpretation is row wise
  uint8* getPixels() { return mData.get(); }
  const uint8* getPixels() const { return mData.get(); }

  size_t getPixelsSize() const { return pixelFormatImageSize(mPixelFormat, mWidth, mHeight); }

  PixelFormat getPixelFormat() const { return mPixelFormat; }

private:
  void resizeInternalPtr();

private:
  std::unique_ptr<uint8> mData;
  unsigned mWidth;
  unsigned mHeight;
  PixelFormat mPixelFormat;
};

} // namespace aw
