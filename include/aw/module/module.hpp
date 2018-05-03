#pragma once

#include <string>
#include <unordered_map>

namespace aw
{
namespace reflect
{
class TypeDescriptor;
}

namespace module
{

class Module
{
public:
  typedef std::unordered_map<std::string, reflect::TypeDescriptor*> TypeMap;

public:
  void addType(reflect::TypeDescriptor* typeDescriptor);

  reflect::TypeDescriptor* getType(std::string name) const;
  TypeMap::const_iterator begin() const
  {
    return mTypes.cbegin();
  };
  TypeMap::const_iterator end() const
  {
    return mTypes.cend();
  };

private:
private:
  TypeMap mTypes;
};

} // namespace module
} // namespace aw
