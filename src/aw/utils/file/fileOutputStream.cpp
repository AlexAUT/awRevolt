#include <aw/utils/file/fileOutputStream.hpp>

#include <cassert>

namespace aw
{
FileOutputStream::FileOutputStream(Path path)
{
  assert(path.getType() != aw::Path::Type::Asset && "Never write to asset directory");

  const auto& absPath = path.asString();

  mFileStream.open(absPath);
  rdbuf(mFileStream.rdbuf());
}

FileOutputStream::~FileOutputStream() {}

bool FileOutputStream::isOpen() const
{
  return mFileStream.is_open();
}
} // namespace aw
