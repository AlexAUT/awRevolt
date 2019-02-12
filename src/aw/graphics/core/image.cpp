#include <aw/graphics/core/image.hpp>

#include <aw/utils/file/fileInputStream.hpp>
#include <aw/utils/log.hpp>
#include <aw/utils/streamReading.hpp>

DEFINE_LOG_CATEGORIES(Image, "Image")

#define STB_IMAGE_IMPLEMENTATION
#include <aw/graphics/core/stb_image.hpp>

#include <cstring>

namespace aw
{
bool Image::load(const aw::Path& path)
{
  FileInputStream stream(path);
  if (!stream.isOpen())
  {
    LogErrorImage() << "Failed to open path: " << path;
    return false;
  }
  std::vector<uint8> fileBuffer = stream::toUint8(stream);
  uint8* ptr =
      stbi_load_from_memory(fileBuffer.data(), fileBuffer.size(), &mWidth, &mHeight, &mNumChannels, STBI_default);

  if (ptr)
  {
    size_t size = mWidth * mHeight * mNumChannels; // 4 components 4bytes each, for every pixel
    mData.resize(size);
    std::memcpy(mData.data(), ptr, size);
    stbi_image_free(ptr);

    // Set pixel format
    switch (mNumChannels)
    {
    case 1:
      mPixelFormat = PixelFormat::R8;
      break;
    case 2:
      mPixelFormat = PixelFormat::RG16;
      break;
    case 3:
      mPixelFormat = PixelFormat::RGB24;
      break;
    case 4:
      mPixelFormat = PixelFormat::RGBA32;
      break;
    }

    return true;
  }
  else
    LogErrorImage() << "Failed to load image!";

  return false;
}

Image Image::convertToPixelFormat(const Image& image, PixelFormat newFormat)
{
  Image newImage;
  newImage.mHeight = image.mHeight;
  newImage.mWidth = image.mWidth;
  newImage.mPixelFormat = newFormat;
  newImage.mNumChannels = pixelFormatToChannelCount(newFormat);

  const auto numPixels = image.mWidth * image.mHeight;
  const auto sizePerPixel = pixelFormatToPixelSize(newFormat);
  LogTemp() << "Space: " << newImage.mNumChannels << ", " << sizePerPixel;
  newImage.mData.resize(numPixels * sizePerPixel);
  LogTemp() << image.mData.size() << " < " << newImage.mData.size();

  if (newFormat == PixelFormat::RGBFloat)
  {
    if (image.getPixelFormat() == PixelFormat::RGB24)
    {
      const uint8* oldImageIter = reinterpret_cast<const uint8*>(image.mData.data());
      float* newImageIter = reinterpret_cast<float*>(newImage.mData.data());

      for (int i = 0u; i < numPixels * 3; i++)
      {
        if (i < 3)
          LogTemp() << "Pixel: " << (int)*oldImageIter;
        *newImageIter = static_cast<float>(*oldImageIter) / 255.f;
        newImageIter++;
        oldImageIter++;
      }
    }
    else
    {
      assert(false && "Conversion not supported yet");
    }
  }
  else if (newFormat == PixelFormat::RGBAFloat)
  {
    if (image.getPixelFormat() == PixelFormat::RGB24)
    {
      const uint8* oldImageIter = reinterpret_cast<const uint8*>(image.mData.data());
      float* newImageIter = reinterpret_cast<float*>(newImage.mData.data());

      int counter = 0;
      for (int i = 0u; i < numPixels * 4; i++)
      {
        if (++counter == 4)
        {
          counter = 0;
          *newImageIter = 1.f;
        }
        else
        {
          *newImageIter = static_cast<float>(*oldImageIter) / 255.f;
          oldImageIter++;
        }
        newImageIter++;
      }
    }
    else
    {
      assert(false && "Conversion not supported yet");
    }
  }
  else
  {
    assert(false && "Conversion not supported yet");
  }

  return newImage;
}

} // namespace aw
