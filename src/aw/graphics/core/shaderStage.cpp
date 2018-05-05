#include <aw/graphics/core/shaderStage.hpp>

#include <aw/opengl/opengl.hpp>

#include <aw/utils/log.hpp>
#include <aw/utils/streamReading.hpp>

DEFINE_LOG_CATEGORY(ShaderStageE, aw::log::Error, ShaderStage)

namespace aw
{
ShaderStage::ShaderStage(Type type) : mType(type), mId(0)
{
}

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
  mId = GL_CHECK(glCreateShader(getGLType()));
  GL_CHECK(glShaderSource(mId, 1, &content, nullptr));
  GL_CHECK(glCompileShader(mId));

  int success;
  glGetShaderiv(mId, GL_COMPILE_STATUS, &success);
  if (!success)
  {
    char infoLog[512];
    glGetShaderInfoLog(mId, 512, nullptr, infoLog);
    GL_CHECK(glDeleteShader(mId));
    mId = 0;
    LogShaderStageE() << "Failed when compiling shader stage:\n " << infoLog << "\n\n Content: " << content;
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
  }
}

unsigned ShaderStage::getId() const
{
  return mId;
}

} // namespace aw
