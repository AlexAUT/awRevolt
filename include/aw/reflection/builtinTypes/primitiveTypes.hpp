#include <aw/reflection/typeDescriptor.hpp>
#include <aw/reflection/typeResolver.hpp>

#include <iostream>

namespace aw::reflect
{
class PrimitiveTypeDescriptorBase
{
};

template <typename PrimitiveType>
class PrimitiveTypeDescriptor : public TypeDescriptor, public PrimitiveTypeDescriptorBase
{
public:
  PrimitiveTypeDescriptor(const char* name) : TypeDescriptor(name, sizeof(PrimitiveType)) {}

  // To be consistent with other typedescriptors
  const PrimitiveType& getValue(const PrimitiveType& type) const { return type; }
};
template <>
auto& getPrimitiveDescriptor<char>()
{
  static PrimitiveTypeDescriptor<char> instance("char");
  return instance;
}

template <>
auto& getPrimitiveDescriptor<unsigned char>()
{
  static PrimitiveTypeDescriptor<char> instance("uchar");
  return instance;
}

template <>
auto& getPrimitiveDescriptor<int>()
{
  static PrimitiveTypeDescriptor<int> instance("int");
  return instance;
}

template <>
auto& getPrimitiveDescriptor<unsigned>()
{
  static PrimitiveTypeDescriptor<unsigned> instance("uint");
  return instance;
}

template <>
auto& getPrimitiveDescriptor<float>()
{
  static PrimitiveTypeDescriptor<float> instance("float");
  return instance;
}

template <>
auto& getPrimitiveDescriptor<double>()
{
  static PrimitiveTypeDescriptor<double> instance("double");
  return instance;
}
} // namespace aw::reflect

