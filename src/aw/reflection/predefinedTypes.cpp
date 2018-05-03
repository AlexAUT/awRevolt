#include <aw/reflection/typeDescriptor.hpp>
#include <aw/reflection/typeResolver.hpp>

#include <iostream>

namespace aw
{
namespace reflect
{

class TypeDescriptor_Int : public TypeDescriptor
{
public:
  TypeDescriptor_Int() : TypeDescriptor("int", sizeof(int))
  {
  }

  void debugPrint(const void* instance, int) const override
  {
    std::cout << "int{" << *(const int*)instance << "}";
  }
};

template <>
TypeDescriptor* getPrimitiveDescriptor<int>()
{
  static TypeDescriptor_Int instance;
  return &instance;
}

} // namespace reflect
} // namespace aw
