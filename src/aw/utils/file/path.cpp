#include <aw/utils/file/path.hpp>

#ifdef AW_ANDROID
#include <SFML/System/NativeActivity.hpp>
#include <android/native_activity.h>
#endif

#include <aw/utils/log.hpp>

namespace aw
{
Path::Path(Type type, std::string_view relativePath)
{
  mCompletePath = getBasePath(type);
  mBasePathView = mCompletePath;
  mCompletePath += relativePath;
  mRelativePathView = {mCompletePath.data() + mBasePathView.size(), mCompletePath.size() - mBasePathView.size()};
}

void Path::append(const std::string_view part)
{
  if (mCompletePath.back() != '/' && mCompletePath.back() != '\\')
    mCompletePath.push_back('/');
  mCompletePath.append(part);
  mRelativePathView = {mCompletePath.data() + mBasePathView.size(), mCompletePath.size() - mBasePathView.size()};
}

Path operator+(const Path& path, std::string_view toAdd)
{
  Path result = path;
  result.append(toAdd);
  return result;
}

std::string Path::getExtension() const
{
  auto lastSlashPos = mRelativePathView.find_last_of('/');
  if (lastSlashPos == std::string::npos)
    lastSlashPos = 0;
  auto dotPos = mRelativePathView.find_last_of('.');
  if (dotPos > lastSlashPos && dotPos < mRelativePathView.size() - 1)
    return std::string(mRelativePathView.substr(dotPos + 1));

  return "";
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
  stream << "Path: { " << typeToString(path.getType()) << ": " << path.asString() << " } ";

  return stream;
}
