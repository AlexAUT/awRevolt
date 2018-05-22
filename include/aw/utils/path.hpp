#pragma once

#include <string>

namespace aw
{
namespace path
{

enum Type
{
  ABSOLUTE,
  INTERNAL,
  EXTERNAL,
  ASSET,
};

std::string getAssetPath();
std::string getInternal();
std::string getExternal();
std::string getConfigPath();
} // namespace path
} // namespace aw
