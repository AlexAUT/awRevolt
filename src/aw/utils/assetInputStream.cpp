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
  mFileStream.open(path.c_str());
  rdbuf(mFileStream.rdbuf());
#elif AW_ANDROID
  rdbuf(new AndroidAssetBuffer(path));
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
#ifdef AW_DESKTOP
  return mFileStream.is_open() && !mFileStream.fail();
#endif
  return good();
}

} // namespace aw
