#include <aw/utils/impl/androidAssetBuffer.hpp>

#include <SFML/System/NativeActivity.hpp>

namespace aw
{

AndroidAssetBuffer::AndroidAssetBuffer(const std::string& filePath)
{
  ANativeActivity* activity = sf::getNativeActivity();
  mAsset = AAssetManager_open(activity->assetManager, filePath.c_str(), AASSET_MODE_STREAMING);

  if (mAsset)
  {
    mBuffer.resize(1024);

    setg(0, 0, 0);
    setp(&mBuffer.front(), &mBuffer.front() + mBuffer.size());
  }
}

AndroidAssetBuffer::~AndroidAssetBuffer()
{
  if (mAsset)
  {
    sync();
    AAsset_close(mAsset);
  }
}

std::streambuf::int_type AndroidAssetBuffer::underflow()
{
  auto bufferPtr = &mBuffer.front();
  auto counter = AAsset_read(mAsset, bufferPtr, mBuffer.size());

  if (counter == 0)
    return traits_type::eof();
  if (counter < 0) // error, what to do now?
    return traits_type::eof();

  setg(bufferPtr, bufferPtr, bufferPtr + counter);

  return traits_type::to_int_type(*gptr());
}

std::streambuf::int_type AndroidAssetBuffer::overflow(std::streambuf::int_type value)
{
  return traits_type::eof();
};

int AndroidAssetBuffer::sync()
{
  std::streambuf::int_type result = overflow(traits_type::eof());

  return traits_type::eq_int_type(result, traits_type::eof()) ? -1 : 0;
}

bool AndroidAssetBuffer::isOpen() const
{
  return mAsset != nullptr;
}

} // namespace aw
