#include <aw/utils/streamReading.hpp>

namespace aw
{
namespace stream
{
std::string toString(std::istream& stream, size_t chunkSize)
{

  const size_t CHUNK_SIZE = 2048;
  std::string stringBuffer;
  stringBuffer.resize(chunkSize);
  size_t cursor = 0;
  size_t readBytes;
  while (stream.read(reinterpret_cast<char*>(stringBuffer.data() + cursor), chunkSize))
  {
    cursor += chunkSize;
    stringBuffer.resize(cursor + chunkSize);
  }
  stringBuffer.resize(cursor + stream.gcount());

  return stringBuffer;
}

std::vector<uint8> toUint8(std::istream& stream, size_t chunkSize)
{
  const size_t CHUNK_SIZE = 2048;
  std::vector<uint8> buffer(chunkSize);
  size_t cursor = 0;
  size_t readBytes;
  while (stream.read(reinterpret_cast<char*>(buffer.data() + cursor), chunkSize))
  {
    cursor += chunkSize;
    buffer.resize(cursor + chunkSize);
  }
  buffer.resize(cursor + stream.gcount());

  return buffer;
}
} // namespace stream
} // namespace aw
