#pragma once

#include <aw/utils/path.hpp>

#include <fstream>
#include <istream>

namespace aw
{

class AssetInputStream : public std::istream
{
public:
  AssetInputStream(std::string path);
  ~AssetInputStream();

  bool isOpen() const;

private:
private:
  std::ifstream mFileStream;
};

} // namespace aw
