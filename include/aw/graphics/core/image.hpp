#pragma once

#include <aw/utils/types.hpp>

#include <istream>
#include <string>
#include <vector>

namespace aw
{

class Image
{
public:
  bool loadFromStream(std::istream& stream, bool invertYAxis = false);

  int getWidth() const
  {
    return mWidth;
  }
  int getHeight() const
  {
    return mHeight;
  }
  int getNumChannels() const
  {
    return mNumChannels;
  }

private:
private:
  std::vector<uint8> mData;
  int mWidth;
  int mHeight;
  int mNumChannels;
};

} // namespace aw
