#include <aw/utils/file/fileDialog.hpp>

namespace aw::fileDialog
{
Path openFile(const std::string& title, const std::string& defaultPath, const char** allowedExtensions,
              size_t numOfExtensions, const std::string& filterDescription, bool allowMultipleFiles)
{
  auto* result = tinyfd_openFileDialog(title.c_str(), defaultPath.c_str(), numOfExtensions, allowedExtensions,
                                       filterDescription.c_str(), allowMultipleFiles);
  if (result)
    return createAbsolutePath(result);
  return createAbsolutePath("");
}

Path openFolder(const std::string& title, const std::string& defaultPath)
{
  auto* result = tinyfd_selectFolderDialog(title.c_str(), defaultPath.c_str());

  if (result)
    return createAbsolutePath(result);
  return createAbsolutePath("");
}

std::string textDialog(const std::string& title, const std::string& message, const std::string& defaultValue)
{
  auto* result = tinyfd_inputBox(title.c_str(), message.c_str(), defaultValue.c_str());
  if (result)
    return result;
  return "";
}

Path saveFile(const std::string& title, const std::string& defaultPath, const char** allowedExtensions,
              size_t numOfExtensions, const std::string& filterDescription)
{
  auto* result = tinyfd_saveFileDialog(title.c_str(), defaultPath.c_str(), numOfExtensions, allowedExtensions,
                                       filterDescription.c_str());
  if (result)
    return createAbsolutePath(result);
  return createAbsolutePath("");
}
} // namespace aw::fileDialog
