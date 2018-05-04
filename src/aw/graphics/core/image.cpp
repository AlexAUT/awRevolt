#include <aw/graphics/core/image.hpp>

#define STB_IMAGE_IMPLEMENTATION
#include <aw/graphics/core/stb_image.hpp>

namespace aw
{
bool Image::loadFromStream(std::istream& stream, bool invertYAxis)
{
  const size_t CHUNK_SIZE = 2048;
  std::vector<uint8> fileBuffer(CHUNK_SIZE);
  size_t cursor = 0;
  size_t readBytes;
  while (stream.read(reinterpret_cast<char*>(fileBuffer.data() + cursor), CHUNK_SIZE))
  {
    cursor += CHUNK_SIZE;
    fileBuffer.resize(cursor + CHUNK_SIZE);
  }
  fileBuffer.resize(cursor + stream.gcount());

  uint8* ptr =
      stbi_load_from_memory(fileBuffer.data(), fileBuffer.size(), &mWidth, &mHeight, &mNumChannels, STBI_rgb_alpha);
  if (ptr)
  {
    if (invertYAxis)
    {
      uint32* ptr_32 = reinterpret_cast<uint32*>(ptr);
      auto* buffer = new uint32_t[mWidth];
      for (std::size_t i = 0; i < mHeight / 2; i++)
      {
        // Swap i with h - i - 1
        auto j = mHeight - i - 1;
        std::copy(&ptr_32[i * mWidth], &ptr_32[(i + 1) * mWidth], buffer);
        std::copy(&ptr_32[j * mWidth], &ptr_32[(j + 1) * mWidth], &ptr_32[i * mWidth]);
        std::copy(&buffer[0], &buffer[mWidth], &ptr_32[j * mWidth]);
      }
      delete[](buffer);
    }
    size_t size = mWidth * mHeight * mNumChannels; // 4 components 4bytes each, for every pixel
    mData.resize(size);
    stbi_image_free(ptr);

    return true;
  }

  return false;
}

} // namespace aw
