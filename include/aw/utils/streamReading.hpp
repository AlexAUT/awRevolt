#pragma once

#include <aw/utils/types.hpp>

#include <istream>
#include <string>
#include <vector>

namespace aw
{
namespace stream
{
std::string toString(std::istream& stream, size_t chunkSize = 2048);
std::vector<uint8> toUint8(std::istream& stream, size_t chunkSize = 2048);
} // namespace stream
} // namespace aw
