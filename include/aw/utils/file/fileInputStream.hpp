#pragma once

#include <aw/config.hpp>
#include <aw/utils/file/path.hpp>

#include <fstream>

namespace aw
{

class FileInputStream : public std::istream
{
public:
  FileInputStream(Path path);
  ~FileInputStream();

  bool isOpen() const;

  const Path& getPath() const { return mPath; }

private:
private:
  Path mPath;
  std::ifstream mFileStream;
  bool mIsOpen;

#ifdef AW_ANDROID
  bool mIsAssetFile{false};
#endif
};

} // namespace aw
