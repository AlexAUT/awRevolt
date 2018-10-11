#pragma once

#include <aw/utils/path.hpp>

#include <fstream>
#include <istream>

namespace aw
{

class AssetInputStream : std::istream
{
public:
  AssetInputStream(std::string path);
  ~AssetInputStream();

private:
private:
  std::ifstream mFileStream;
};

} // namespace aw
