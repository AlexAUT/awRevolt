#include <aw/module/exporter.hpp>
#include <iostream>

namespace aw
{
namespace module
{
namespace exporter
{
ModuleMap moduleMap;

Module getModule(std::string name)
{
  auto found = moduleMap.find(name);
  if (found != moduleMap.end())
    return found->second;
  return {};
}

void addModule(std::string name, const Module& module)
{
  moduleMap[name] = module;
}

void addTypeToModule(std::string moduleName, reflect::TypeDescriptor* typeDescritor)
{
  moduleMap[moduleName].addType(typeDescritor);
}

ModuleMap::const_iterator cbegin()
{
  return moduleMap.cbegin();
}

ModuleMap::const_iterator cend()
{
  return moduleMap.cend();
}

} // namespace exporter
} // namespace module
} // namespace aw

extern "C" const void* hello()
{
  std::cout << "Hallo Welt" << std::endl;
  return &aw::module::exporter::moduleMap;
}
