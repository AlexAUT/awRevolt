#pragma once

#include <aw/reflection/typeDescriptorClass.hpp>
#include <aw/utils/log.hpp>

namespace aw::reflect::op
{
std::string getIdent(int identLevel)
{
  return std::string(2 * identLevel, ' ');
}
template <typename Class, typename DescriptorType>
void print(const Class& instance, DescriptorType& descriptor, const aw::log::LogInstance& logger, int identLevel = 0)
{
  if constexpr (std::is_base_of_v<PrimitiveTypeDescriptorBase, DescriptorType>)
  {
    logger << descriptor.getName() << "{ " << descriptor.getValue(instance) << " }";
  }
  if constexpr (std::is_base_of_v<ClassTypeDescriptorBase, DescriptorType>)
  {
    logger << descriptor.getName() << "{\n";
    descriptor.forAllMembers([&instance, &logger, identLevel](const auto& member) {
      using MemberType = std::remove_reference_t<decltype(member)>;
      auto& underlying = MemberType::getUnderlyingDescriptor();

      logger << getIdent(identLevel + 1) << member.getName() << ": ";
      print(member.getValue(instance), underlying, logger, identLevel + 1);
      logger << "\n";
    });
    logger << getIdent(identLevel) << "}";
  }
  static_assert(true, "Provided typedescriptor not supported by the print function!");
}

template <typename Class>
void print(const Class& instance, const aw::log::LogInstance& logger, int identLevel = 0)
{
  auto& staticClass = aw::reflect::getReflection<Class>();
  logger << "\n";
  print(instance, staticClass, logger);
}
} // namespace aw::reflect::op
