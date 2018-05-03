#pragma once

#include <aw/reflection/typeDescriptor.hpp>

#include <aw/utils/types.hpp>

#include <functional>
#include <iostream>
#include <string>
#include <vector>

namespace aw
{
namespace reflect
{

class TypeDescriptorStruct : public TypeDescriptor
{
public:
  struct Member
  {
    std::string name;
    size_t offset;
    TypeDescriptor* type;
  };

  explicit TypeDescriptorStruct(std::function<void(TypeDescriptorStruct*)> fn) : TypeDescriptor("", 0)
  {
    fn(this);
  }

  TypeDescriptorStruct(std::string name, size_t size, const std::initializer_list<Member>& init)
      : TypeDescriptor("", 0), members{init}
  {
  }

  ~TypeDescriptorStruct(){};

  void debugPrint(const void* instance, int indentLevel = 0) const override
  {
    std::cout << name << "{" << std::endl;
    const byte* instanceBytePtr = (const byte*)instance;
    for (const auto& member : members)
    {
      std::cout << std::string(2 * (indentLevel + 1), ' ') << member.name << " = ";
      member.type->debugPrint(instanceBytePtr + member.offset, indentLevel + 1);
      std::cout << std::endl;
    }
    std::cout << "}" << std::endl;
  }

public:
  std::vector<Member> members;
}; // namespace reflect

} // namespace reflect
} // namespace aw
