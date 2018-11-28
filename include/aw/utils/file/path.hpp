#pragma once

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
  const std::string getAbsolutePath() const { return Path::getBasePath(mType) + getRelativePath(); }

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
} // namespace aw
