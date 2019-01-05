#pragma once

#include <aw/utils/types.hpp>

#include <string>

namespace aw
{
namespace reflect
{

class TypeDescriptor
{
public:
  TypeDescriptor(std::string name, size_t size) : mName{name}, mSize{size} {};
  virtual ~TypeDescriptor(){};

  std::string_view getName() const { return mName; }
  size_t getSize() const { return mSize; }

private:
  std::string mName;
  size_t mSize;
};

} // namespace reflect
} // namespace aw
