#include <aw/graphics/core/shaderStage.hpp>

#include <aw/config.hpp>
#include <aw/opengl/opengl.hpp>
#include <aw/utils/file/fileInputStream.hpp>
#include <aw/utils/file/path.hpp>
#include <aw/utils/log.hpp>
#include <aw/utils/streamReading.hpp>

DEFINE_LOG_CATEGORIES(ShaderStage, "Shaderstage")

namespace aw
{
std::unique_ptr<ShaderStage> ShaderStage::loadFromPath(Type type, const Path& path)
{
  auto result = std::make_unique<ShaderStage>(type);
  aw::FileInputStream stream(path);
  result->loadFromStream(stream);
  return result;
}

ShaderStage::ShaderStage(Type type) : mType(type), mId(0) {}

ShaderStage::~ShaderStage()
{
  if (mType != 0)
    glDeleteShader(mType);
}

bool ShaderStage::loadFromStream(std::istream& stream)
{
  std::string content = stream::toString(stream);
  return loadFromMemory(content.data());
}

bool ShaderStage::loadFromMemory(const char* content)
{
  GL_CHECK(mId = glCreateShader(getGLType()));

  const char* prefix = "";
// Add a prefix to make shaders compatible between opengl and opengl es
#ifdef AW_DESKTOP
  if (mType == Type::Vertex)
    prefix = "#version 330\n";
  if (mType == Type::Fragment)
    prefix = "#version 330\n";
#else
  if (mType == Type::Fragment)
    prefix = "precision mediump float;\n";
#endif

  const char* combined[2] = {prefix, content};

  GL_CHECK(glShaderSource(mId, 2, combined, nullptr));
  GL_CHECK(glCompileShader(mId));

  int success;
  glGetShaderiv(mId, GL_COMPILE_STATUS, &success);
  if (!success)
  {
    char infoLog[512];
    glGetShaderInfoLog(mId, 512, nullptr, infoLog);
    GL_CHECK(glDeleteShader(mId));
    mId = 0;
    LogErrorShaderStage() << "Failed when compiling shader stage:\n " << infoLog << "\n\n Content: " << content;
    return false;
  }
  return true;
}

ShaderStage::Type ShaderStage::getType() const
{
  return mType;
}

GLenum ShaderStage::getGLType() const
{
  switch (mType)
  {
  case Vertex:
    return GL_VERTEX_SHADER;
  case Fragment:
    return GL_FRAGMENT_SHADER;
  default:
    return GL_VERTEX_SHADER;
  }
}

unsigned ShaderStage::getId() const
{
  return mId;
}

} // namespace aw
