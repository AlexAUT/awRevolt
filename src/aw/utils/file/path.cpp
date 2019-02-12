#include <aw/utils/file/path.hpp>

#ifdef AW_ANDROID
#include <SFML/System/NativeActivity.hpp>
#include <android/native_activity.h>
#endif

#include <aw/utils/log.hpp>

namespace aw
{
void Path::append(const std::string_view part)
{
  if (mRelativePath.back() != '/' && mRelativePath.back() != '\\')
    mRelativePath.push_back('/');
  mRelativePath.append(part);
}

Path operator+(const Path& path, std::string_view toAdd)
{
  Path result = path;
  result.append(toAdd);
  return result;
}

std::string_view Path::getExtension() const
{
  auto lastSlashPos = mRelativePath.find_last_of('/');
  if (lastSlashPos == std::string::npos)
    lastSlashPos = 0;
  auto dotPos = mRelativePath.find_last_of('.');
  if (dotPos > lastSlashPos && dotPos < mRelativePath.size() - 1)
  {
    auto view = std::string_view{mRelativePath.data() + dotPos + 1, mRelativePath.size() - dotPos - 1};
    return view;
  }

  return {};
}

std::string Path::getAssetPath()
{
#ifdef AW_DESKTOP
  return "assets/";
#endif
  return "";
}

std::string Path::getInternal()
{
#ifdef AW_DESKTOP
  return "";
#elif AW_ANDROID
  ANativeActivity* activity = sf::getNativeActivity();
  return std::string(activity->internalDataPath) + "/";
#endif
  return "";
}
std::string Path::getExternal()
{
#ifdef AW_DESKTOP
  return "";
#elif AW_ANDROID
  ANativeActivity* activity = sf::getNativeActivity();
  return std::string(activity->externalDataPath) + "/";
#endif
  return "";
}

std::string Path::getConfigPath()
{
#ifdef AW_DESKTOP
  return "config/";
#elif AW_ANDROID
  return getInternal();
#endif
  return "";
}

std::string Path::getBasePath(Type type)
{
  switch (type)
  {
  case Type::Asset:
    return getAssetPath();
  case Type::Internal:
    return getInternal();
  case Type::External:
    return getExternal();
  case Type::Config:
    return getConfigPath();
  default:
    return "";
  }
}

} // namespace aw

const char* typeToString(aw::Path::Type type)
{
  using Type = aw::Path::Type;
  switch (type)
  {
  case Type::Absolute:
    return "Absolute";
  case Type::Asset:
    return "Asset";
  case Type::Config:
    return "Config";
  case Type::External:
    return "External";
  case Type::Internal:
    return "Internal";
  default:
    return "Unknown path type";
  }
}

std::ostream& operator<<(std::ostream& stream, const aw::Path& path)
{
  stream << "Path: { " << typeToString(path.getType()) << ": " << path.getCompletePath() << " } ";

  return stream;
}
