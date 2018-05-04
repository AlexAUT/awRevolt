#pragma once

#include <streambuf>

namespace aw
{
class AndroidStreamBuffer : public std::streambuf
{
public:
  static const int BUFFER_SIZE = 128;

  AndroidStreamBuffer();

private:
  int overflow(int c);
  int sync();

  char buffer[BUFFER_SIZE];
};

} // namespace aw
