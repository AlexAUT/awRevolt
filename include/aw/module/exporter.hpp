#pragma once

#include <aw/module/module.hpp>

#include <string>
#include <unordered_map>

namespace aw
{
namespace reflect
{
class TypeDescriptor;
} // namespace reflect

namespace module
{
namespace exporter
{
typedef std::unordered_map<std::string, Module> ModuleMap;

void addModule(std::string name, const Module& module);
void addTypeToModule(std::string moduleName, reflect::TypeDescriptor* typeDescriptor);

Module getModule(std::string name);
ModuleMap::const_iterator cbegin();
ModuleMap::const_iterator cend();

#define EXPORT_STRUCT(ModuleName, StructName)                                                                          \
  std::cout << "EXPORT STRUCT: " << #ModuleName << std::endl;                                                          \
  aw::module::exporter::addTypeToModule(#ModuleName, &StructName::reflection);

} // namespace exporter
} // namespace module
} // namespace aw
