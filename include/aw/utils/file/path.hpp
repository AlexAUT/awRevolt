#pragma once

#include <ostream>
#include <string>

namespace aw
{
class Path
{
public:
  enum class Type
  {
    Asset,
    Internal,
    External,
    Config,
    Absolute
  };

public:
  static std::string getAssetPath();
  static std::string getInternal();
  static std::string getExternal();
  static std::string getConfigPath();

  static std::string getBasePath(Type type);

public:
  Path() = default;
  Path(Type type, std::string relativePath) : mRelativePath(std::move(relativePath)), mType(type) {}
  Path(Type type, std::string_view relativePath) : mRelativePath(relativePath), mType(type){};

  Type getType() const { return mType; }
  const std::string& getRelativePath() const { return mRelativePath; }
  const std::string getCompletePath() const { return Path::getBasePath(mType) + getRelativePath(); }

private:
private:
  std::string mRelativePath;
  Type mType;
};

inline Path createAssetPath(std::string relativePath)
{
  return Path(Path::Type::Asset, relativePath);
}
inline Path createInternalPath(std::string relativePath)
{
  return Path(Path::Type::Internal, relativePath);
}
inline Path createExternalPath(std::string relativePath)
{
  return Path(Path::Type::External, relativePath);
}
inline Path createConfigPath(std::string relativePath)
{
  return Path(Path::Type::Config, relativePath);
}
inline Path createAbsolutePath(std::string absolutePath)
{
  return Path(Path::Type::Absolute, absolutePath);
}
namespace pathLiterals
{
inline Path operator"" _asset(const char* relativePath)
{
  return createAssetPath(relativePath);
}
inline Path operator"" _internal(const char* relativePath)
{
  return createInternalPath(relativePath);
}
inline Path operator"" _external(const char* relativePath)
{
  return createExternalPath(relativePath);
}
inline Path operator"" _config(const char* relativePath)
{
  return createConfigPath(relativePath);
}
inline Path operator"" _absolute(const char* absolutePath)
{
  return createAbsolutePath(absolutePath);
}
} // namespace pathLiterals
} // namespace aw
std::ostream& operator<<(std::ostream& stream, const aw::Path& vec);
