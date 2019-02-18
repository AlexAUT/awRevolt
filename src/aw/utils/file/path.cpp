#include <aw/utils/file/path.hpp>

#ifdef AW_ANDROID
#include <SFML/System/NativeActivity.hpp>
#include <android/native_activity.h>
#endif

#include <aw/utils/log.hpp>

namespace aw
{
Path::Path(Type type, std::string_view relativePath) : mType(type)
{
  mPath = getBasePath(type);
  if (mPath.size() > 1 && mPath.back() == '/')
    mPath.pop_back();

  append(relativePath);
}

Path::Path(std::string path) : mPath(path), mType(Path::Type::Custom) {}

void Path::append(std::string_view part)
{
  if (part.empty() || part.find_first_not_of('/') == std::string::npos)
    return;

  if (part.front() != '/' && !mPath.empty())
    mPath.push_back('/');

  mPath.append(part);
  if (mPath.size() > 1 && mPath.back() == '/')
    mPath.pop_back();
}

void Path::removeBasePath(const Path& base)
{
  auto cutPos = mPath.find_first_not_of(base.mPath);
  if (cutPos != std::string::npos)
  {
    mPath.erase(0, cutPos);
  }
}

Path operator+(const Path& path, std::string_view toAdd)
{
  Path result = path;
  result.append(toAdd);
  return result;
}

Path operator-(const Path& fullPath, const Path& partToRemove)
{
  Path result = fullPath;
  result.removeBasePath(partToRemove);
  return result;
}

std::string Path::getFileName() const
{
  if (mPath.empty())
    return "";

  auto lastSlashPos = mPath.find_last_of('/');
  if (lastSlashPos == std::string::npos)
    return mPath;

  auto dotPos = mPath.find_last_of('.');
  if (dotPos == std::string::npos || dotPos < lastSlashPos)
    return mPath.substr(lastSlashPos + 1);
  else
    return mPath.substr(lastSlashPos + 1, dotPos - 1 - lastSlashPos);
}

std::string Path::getExtension() const
{
  auto lastSlashPos = mPath.find_last_of('/');
  if (lastSlashPos == std::string::npos)
    lastSlashPos = 0;
  auto dotPos = mPath.find_last_of('.');
  if (dotPos > lastSlashPos && dotPos < mPath.size() - 1)
    return std::string(mPath.substr(dotPos));

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
