#pragma once

#include <aw/utils/file/path.hpp>

#include <array>
#include <string>

#include <tinyfiledialogs.h>

namespace aw::fileDialog
{
template <int numOfExtensions>
Path openFile(const std::string& title, const std::string& defaultPath,
              std::array<const char*, numOfExtensions> allowedExtensions, const std::string& filterDescription,
              bool allowMultipleFiles)
{
  auto* result = tinyfd_openFileDialog(title.c_str(), defaultPath.c_str(), allowedExtensions.size(),
                                       allowedExtensions.data(), filterDescription.c_str(), allowMultipleFiles);
  if (result)
    return createAbsolutePath(result);
  return createAbsolutePath("");
  ;
}

template <int numOfExtensions>
Path saveFile(const std::string& title, const std::string& defaultPath,
              std::array<const char*, numOfExtensions> allowedExtensions, const std::string& filterDescription)
{
  auto* result = tinyfd_saveFileDialog(title.c_str(), defaultPath.c_str(), allowedExtensions.size(),
                                       allowedExtensions.data(), filterDescription.c_str());
  if (result)
    return createAbsolutePath(result);
  return createAbsolutePath("");
  ;
}
} // namespace aw::fileDialog
