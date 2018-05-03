#pragma once

#include <aw/reflection/typeDescriptorStruct.hpp>
#include <aw/reflection/typeResolver.hpp>

namespace aw
{
#define REFLECT_STRUCT()                                                                                               \
  static aw::reflect::TypeDescriptorStruct reflection;                                                                 \
  static void initReflectionStruct(aw::reflect::TypeDescriptorStruct*);

#define REFLECT_STRUCT_BEGIN(StructName)                                                                               \
  aw::reflect::TypeDescriptorStruct StructName::reflection{StructName::initReflectionStruct};                          \
  void StructName::initReflectionStruct(aw::reflect::TypeDescriptorStruct* typeDescriptor)                             \
  {                                                                                                                    \
    using T = StructName;                                                                                              \
    typeDescriptor->name = #StructName;                                                                                \
    typeDescriptor->size = sizeof(StructName);

#define REFLECT_STRUCT_MEMBER(name)                                                                                    \
  typeDescriptor->members.push_back({#name, offsetof(T, name), aw::reflect::TypeResolver<decltype(T::name)>::get()});

#define REFLECT_STRUCT_END() }
} // namespace aw
