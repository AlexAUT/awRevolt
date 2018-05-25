#pragma once

#include <istream>

#include <memory>

typedef unsigned GLenum;

namespace aw
{
class ShaderStage
{
public:
  enum Type
  {
    Vertex,
    Fragment,
  };

public:
  static std::unique_ptr<ShaderStage> loadFromAssetFile(Type type, const std::string& path);

public:
  ShaderStage(Type type);
  ~ShaderStage();

  ShaderStage(const ShaderStage&) = delete;
  ShaderStage operator=(const ShaderStage&) = delete;

  bool loadFromStream(std::istream& stream);
  bool loadFromMemory(const char* content);

  Type getType() const;
  GLenum getGLType() const;
  unsigned getId() const;

private:
private:
  Type mType;
  unsigned mId;
};

} // namespace aw
