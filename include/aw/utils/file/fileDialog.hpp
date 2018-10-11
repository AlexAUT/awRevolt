#pragma once

#include <array>
#include <string>

#include <tinyfiledialogs.h>

namespace aw
{
template <int numOfExtensions>
std::string openFileDialog(const std::string& title, const std::string& defaultPath,
                           std::array<const char*, numOfExtensions> allowedExtensions,
                           const std::string& filterDescription, bool allowMultipleFiles)
{
  auto* result = tinyfd_openFileDialog(title.c_str(), defaultPath.c_str(), allowedExtensions.size(),
                                       &allowedExtensions[0], filterDescription.c_str(), allowMultipleFiles);
  if (result)
    return result;
  return {};
}
}
