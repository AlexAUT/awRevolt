#pragma once

#include <type_traits>

namespace aw
{
namespace reflect
{

class TypeDescriptor;

// Declare the function template that handles primitive types such as int, std::string, etc.:
template <typename T>
TypeDescriptor* getPrimitiveDescriptor();

// A helper class to find TypeDescriptors in different ways:
struct DefaultResolver
{
  template <typename T>
  static char func(decltype(&T::Reflection));
  template <typename T>
  static int func(...);
  template <typename T>
  struct IsReflected
  {
    enum
    {
      value = (sizeof(func<T>(nullptr)) == sizeof(char))
    };
  };

  // This version is called if T has a static member named "Reflection":
  template <typename T, typename std::enable_if<IsReflected<T>::value, int>::type = 0>
  static TypeDescriptor* get()
  {
    return &T::reflection;
  }

  // This version is called otherwise:
  template <typename T, typename std::enable_if<!IsReflected<T>::value, int>::type = 0>
  static TypeDescriptor* get()
  {
    return getPrimitiveDescriptor<T>();
  }
};

template <typename T>
class TypeResolver
{
public:
  static TypeDescriptor* get()
  {
    return DefaultResolver::get<T>();
  }
};

} // namespace reflect
} // namespace aw
