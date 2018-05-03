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
  TypeDescriptor(std::string name, size_t size) : name{name}, size{size} {};
  virtual ~TypeDescriptor(){};

  virtual void debugPrint(const void* instance, int indentLevel = 0) const = 0;

  std::string name;
  size_t size;

private:
};

} // namespace reflect
} // namespace aw
