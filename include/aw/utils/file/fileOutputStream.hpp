#pragma once

#include <aw/config.hpp>
#include <aw/utils/file/path.hpp>

#include <fstream>

namespace aw
{

class FileOutputStream : public std::ostream
{
public:
  FileOutputStream(Path path);
  ~FileOutputStream();

  bool isOpen() const;

  const Path& getPath() const { return mPath; }

private:
  Path mPath;
  std::ofstream mFileStream;
  bool mIsOpen;

#ifdef AW_ANDROID
  bool mIsAssetFile{false};
#endif
};

} // namespace aw
