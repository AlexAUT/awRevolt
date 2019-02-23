#pragma once

#include <aw/utils/file/path.hpp>

#include <array>
#include <string>

#include <tinyfd/tinyfiledialogs.h>

namespace aw::fileDialog
{
Path openFile(const std::string& title, const std::string& defaultPath, const char** allowedExtension,
              size_t numOfExtensions, const std::string& filterDescription, bool allowMultipleFiles);
template <int numOfExtensions>
Path openFile(const std::string& title, const std::string& defaultPath,
              std::array<const char*, numOfExtensions> allowedExtensions, const std::string& filterDescription,
              bool allowMultipleFiles);

Path openFolder(const std::string& title, const std::string& defaultPath = "");
std::string textDialog(const std::string& title, const std::string& message, const std::string& defaultValue);

Path saveFile(const std::string& title, const std::string& defaultPath, const char** allowedExtensions,
              size_t numOfExtensions, const std::string& filterDescription);
template <int numOfExtensions>
Path saveFile(const std::string& title, const std::string& defaultPath,
              std::array<const char*, numOfExtensions> allowedExtensions, const std::string& filterDescription);

// IMPLEMENTATION

template <int numOfExtensions>
Path openFile(const std::string& title, const std::string& defaultPath,
              std::array<const char*, numOfExtensions> allowedExtensions, const std::string& filterDescription,
              bool allowMultipleFiles)
{
  return openFile(title, defaultPath, allowedExtensions.data(), allowedExtensions.size(), filterDescription,
                  allowMultipleFiles);
}
template <int numOfExtensions>
Path saveFile(const std::string& title, const std::string& defaultPath,
              std::array<const char*, numOfExtensions> allowedExtensions, const std::string& filterDescription)
{
  return saveFile(title, defaultPath, allowedExtensions.data(), allowedExtensions.size(), filterDescription);
}
} // namespace aw::fileDialog
