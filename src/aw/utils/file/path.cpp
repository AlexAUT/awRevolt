#include <aw/utils/file/path.hpp>

#ifdef AW_ANDROID
#include <SFML/System/NativeActivity.hpp>
#include <android/native_activity.h>
#endif

namespace aw
{
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
