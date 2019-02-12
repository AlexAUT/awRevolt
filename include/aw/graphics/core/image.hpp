#pragma once

#include <aw/graphics/core/pixelFormats.hpp>
#include <aw/utils/types.hpp>

#include <istream>
#include <string>
#include <vector>

namespace aw
{
class Path;

class Image
{
public:
  static Image convertToPixelFormat(const Image& image, PixelFormat newFormat);

public:
  bool load(const aw::Path& path);

  int getWidth() const { return mWidth; }
  int getHeight() const { return mHeight; }
  int getNumChannels() const { return mNumChannels; }
  const uint8* getPixelPtr() const { return mData.data(); }
  const std::vector<uint8> getPixels() const { return mData; }
  PixelFormat getPixelFormat() const { return mPixelFormat; }

private:
private:
  std::vector<uint8> mData;
  int mWidth;
  int mHeight;
  int mNumChannels;
  PixelFormat mPixelFormat;
};

} // namespace aw
