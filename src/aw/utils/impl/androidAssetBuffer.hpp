#pragma once

#include <android/native_activity.h>

#include <streambuf>
#include <string>
#include <vector>

namespace aw
{

class AndroidAssetBuffer : public std::streambuf
{
public:
  AndroidAssetBuffer(const std::string& fileName);
  ~AndroidAssetBuffer();

  std::streambuf::int_type underflow() override;
  std::streambuf::int_type overflow(std::streambuf::int_type value) override;
  int sync() override;

  bool isOpen() const;

private:
  AAsset* mAsset;
  std::vector<char> mBuffer;
};

} // namespace aw
