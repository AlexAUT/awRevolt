#pragma once

#include <aw/utils/types.hpp>

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
    Absolute,
    Custom
  };

public:
  static std::string getAssetPath();
  static std::string getInternal();
  static std::string getExternal();
  static std::string getConfigPath();

  static std::string getBasePath(Type type);

public:
  Path() = default;
  Path(Type type, std::string_view relativePath);
  Path(std::string path);

  Path(const Path&) = default;
  Path(Path&&) = default;
  Path& operator=(const Path&) = default;
  Path& operator=(Path&&) = default;

  Type getType() const { return mType; }
  const std::string& asString() const { return mPath; }

  std::string getFileName() const;
  std::string getFileStem() const;
  std::string getExtension() const;

  void removeFileName();

  void append(std::string_view part);
  void removeBasePath(const Path& base);
  friend Path operator+(const Path& path, std::string_view toAdd);
  friend Path operator-(const Path& fullPath, const Path& partPath);

private:
private:
  std::string mPath;
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
inline Path operator"" _asset(const char* relativePath, size_t length)
{
  return createAssetPath(relativePath);
}
inline Path operator"" _internal(const char* relativePath, size_t length)
{
  return createInternalPath(relativePath);
}
inline Path operator"" _external(const char* relativePath, size_t length)
{
  return createExternalPath(relativePath);
}
inline Path operator"" _config(const char* relativePath, size_t length)
{
  return createConfigPath(relativePath);
}
inline Path operator"" _absolute(const char* absolutePath, size_t length)
{
  return createAbsolutePath(absolutePath);
}
} // namespace pathLiterals
} // namespace aw
std::ostream& operator<<(std::ostream& stream, const aw::Path& vec);
