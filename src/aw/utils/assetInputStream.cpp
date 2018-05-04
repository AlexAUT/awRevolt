#include <aw/utils/assetInputStream.hpp>

#ifdef AW_ANDROID
#include <aw/utils/impl/androidAssetBuffer.hpp>
#endif

namespace aw
{

AssetInputStream::AssetInputStream(std::string path) : std::istream(nullptr)
{
  path = path::getAssetPath() + path;
#ifdef AW_DESKTOP
  mFileStream.open(path.c_str(), std::ios::binary);
  mIsOpen = mFileStream.is_open();
  rdbuf(mFileStream.rdbuf());
#elif AW_ANDROID
  auto* buffer = new AndroidAssetBuffer(path);
  mIsOpen = buffer->isOpen();
  if (mIsOpen)
    rdbuf(buffer);
  else
    delete buffer;
#endif
}

AssetInputStream::~AssetInputStream()
{
#ifdef AW_DESKTOP
  rdbuf(nullptr);
  mFileStream.close();
#elif AW_ANDROID
  delete rdbuf();
#endif
}

bool AssetInputStream::isOpen() const
{
  return mIsOpen;
}

} // namespace aw
