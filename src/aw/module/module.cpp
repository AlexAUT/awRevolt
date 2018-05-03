#include <aw/module/module.hpp>

#include <aw/reflection/typeDescriptor.hpp>

namespace aw
{
namespace module
{

void Module::addType(reflect::TypeDescriptor* typeDescriptor)
{
  mTypes[typeDescriptor->name] = typeDescriptor;
}

reflect::TypeDescriptor* Module::getType(std::string name) const
{
  auto found = mTypes.find(name);
  if (found != mTypes.end())
    return found->second;
  return nullptr;
}

} // namespace module
} // namespace aw
