#pragma once

#include <aw/utils/file/path.hpp>

#include <fstream>
#include <istream>

namespace aw
{

class AssetInputStream : public std::istream
{
public:
  AssetInputStream(std::string path, std::string assetsRoot = path::getAssetPath());
  ~AssetInputStream();

  bool isOpen() const;

private:
private:
  std::ifstream mFileStream;
  bool mIsOpen;
};

} // namespace aw
