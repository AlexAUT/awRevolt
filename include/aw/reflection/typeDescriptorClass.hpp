#pragma once

#include <aw/reflection/builtinTypes/primitiveTypes.hpp>
#include <aw/reflection/reflection.hpp>
#include <aw/reflection/typeDescriptor.hpp>
#include <aw/reflection/typeResolver.hpp>

#include <aw/utils/log.hpp>
#include <aw/utils/typeHelper/staticForLoop.hpp>
#include <aw/utils/types.hpp>

#include <functional>
#include <iostream>
#include <string>
#include <vector>

namespace aw
{
namespace reflect
{
template <typename OwningClass, typename MemberType>
class ClassMember
{
public:
  using MemberPtr = MemberType OwningClass::*;
  using ConstMemberPtr = const MemberType OwningClass::*;

  using ConstRefSetter = void (OwningClass::*)(const MemberType&);
  using ValueSetter = void (OwningClass::*)(const MemberType&);

  using ConstRefGetter = const MemberType& (OwningClass::*)(void)const;

  using UnderylingDescriptor = typename TypeResolver<MemberType>::type;

public:
  ClassMember(std::string name, MemberPtr memberPtr) :
      mName(name),
      mHasMemberPtr(true),
      mMemberPtr(memberPtr),
      mConstMemberPtr(memberPtr)
  {
  }

  ClassMember(std::string name, ConstRefGetter getter) : mName(name), mConstRefGetter(getter) {}

  std::string_view getName() const { return mName; }
  const MemberType& getValue(const OwningClass& instance) const
  {
    if (mHasMemberPtr)
      return instance.*mConstMemberPtr;
    else
      return (instance.*mConstRefGetter)();
  }

  static inline auto& getUnderlyingDescriptor() { return TypeResolver<MemberType>::get(); }

private:
  std::string mName;
  bool mHasMemberPtr{false};
  MemberPtr mMemberPtr{nullptr};
  MemberPtr mConstMemberPtr{nullptr};

  ConstRefGetter mConstRefGetter{nullptr};
};

// Just to make Template handling easier
class ClassTypeDescriptorBase
{
};

template <typename OwningClass, typename... MemberTypes>
class ClassTypeDescriptor : public TypeDescriptor, public ClassTypeDescriptorBase
{
public:
  using Class = OwningClass;

public:
  //  ClassTypeDescriptor(std::string name, size_t size) : TypeDescriptor(name, size) {}
  ClassTypeDescriptor(std::string name, ClassMember<OwningClass, MemberTypes>... members) :
      TypeDescriptor(name, sizeof(OwningClass)),
      mMembers{members...}
  {
  }

  constexpr size_t getMemberCount() const { return sizeof...(MemberTypes); }

  template <typename Function>
  void forAllMembers(Function&& fun)
  {
    staticFor<sizeof...(MemberTypes)>([this, &fun](auto index) { fun(std::get<index>(mMembers)); });
  }

private:
  std::tuple<ClassMember<OwningClass, MemberTypes>...> mMembers;
};

#define REFLECT() static inline auto& getTypeDescriptor();

#define REFLECT_BEGIN(TypeName)                                                                                        \
  template <>                                                                                                          \
  auto& aw::reflect::getReflection<TypeName>()                                                                         \
  {                                                                                                                    \
    using T = TypeName;                                                                                                \
    static ClassTypeDescriptor descriptor                                                                    \
  (                                                                                                                  \
#TypeName

#define REFLECT_MEMBER(name) , ClassMember(#name, &T::name)
#define REFLECT_PRIVATE_MEMBER(name, getter) , ClassMember(#name, getter)

#define REFLECT_END(TypeName)                                                                                          \
);                                                                                                                     \
  return descriptor;                                                                                                   \
  }                                                                                                                    \
  auto& TypeName::getTypeDescriptor() { return aw::reflect::getReflection<TypeName>(); }
} // namespace reflect
} // namespace aw

