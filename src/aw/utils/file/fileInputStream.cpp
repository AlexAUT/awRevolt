#include <aw/utils/file/fileInputStream.hpp>

#include <aw/config.hpp>

#ifdef AW_ANDROID
#include <aw/utils/impl/androidAssetBuffer.hpp>
#endif

namespace aw
{

FileInputStream::FileInputStream(Path path) : std::istream(nullptr), mPath(path)
{
  const auto& absPath = path.asString();
  // Handle android asset file differently because they are zipped inside the apk
#ifdef AW_ANDROID
  if (path.getType() == Path::Type::ASSET)
  {
    auto* buffer = new AndroidAssetBuffer(absPath);
    mIsOpen = buffer->isOpen();
    if (mIsOpen)
      rdbuf(buffer);
    else
      delete buffer;
    return;
  }
#endif
  mFileStream.open(absPath.c_str(), std::ios::binary);
  mIsOpen = mFileStream.is_open();
  rdbuf(mFileStream.rdbuf());
}

FileInputStream::~FileInputStream()
{
#ifdef AW_ANDROID
  if (mIsAssetFile)
  {
    delete rdbuf();
    return;
  }
#endif
  rdbuf(nullptr);
  mFileStream.close();
}

bool FileInputStream::isOpen() const
{
  return mIsOpen;
}

} // namespace aw
