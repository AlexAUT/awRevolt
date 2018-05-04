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
} // namespace path
} // namespace aw
