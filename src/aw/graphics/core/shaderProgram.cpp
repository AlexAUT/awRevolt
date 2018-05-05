#include <aw/graphics/core/shaderProgram.hpp>

#include <aw/opengl/opengl.hpp>

#include <aw/utils/log.hpp>

#include <glm/gtc/type_ptr.hpp>

#include <cassert>

DEFINE_LOG_CATEGORY(ShaderProgramE, aw::log::Error, ShaderProgram)
DEFINE_LOG_CATEGORY(ShaderProgramW, aw::log::Warning, ShaderProgram)

namespace aw
{
ShaderProgram::~ShaderProgram()
{
  if (mProgram != 0)
    glDeleteProgram(mProgram);
}

bool ShaderProgram::link(const ShaderStage& vertexShader, const ShaderStage& fragmentShader)
{
  assert(vertexShader.getGLType() == GL_VERTEX_SHADER);
  assert(fragmentShader.getGLType() == GL_FRAGMENT_SHADER);
  std::vector<std::reference_wrapper<const ShaderStage>> stages;
  stages.push_back(vertexShader);
  stages.push_back(fragmentShader);
  return link(stages);
}

bool ShaderProgram::link(const std::vector<std::reference_wrapper<const ShaderStage>>& shaderStages)
{
  mProgram = GL_CHECK(glCreateProgram());

  for (auto stage : shaderStages)
    GL_CHECK(glAttachShader(mProgram, stage.get().getId()));
  GL_CHECK(glLinkProgram(mProgram));

  int success;
  GL_CHECK(glGetProgramiv(mProgram, GL_LINK_STATUS, &success));
  if (!success)
  {
    char infoLog[512];
    GL_CHECK(glGetProgramInfoLog(mProgram, 512, nullptr, infoLog));
    LogShaderProgramE() << "Cannot link program, error: " << infoLog;
    return false;
  }
  return true;
}

int ShaderProgram::getUniformLocation(std::string name) const
{
  auto cacheEntry = mUniformCache.find(name);
  if (cacheEntry != mUniformCache.end())
    return cacheEntry->second;

  int id = glGetUniformLocation(mProgram, name.c_str());
  if (id == -1)
    LogShaderProgramW() << "Uniform could not be found: " << name;

  mUniformCache.insert({name, id});
  return id;
}

int ShaderProgram::getAttributeLocation(std::string name) const
{
  auto cacheEntry = mAttributeCache.find(name);
  if (cacheEntry != mAttributeCache.end())
    return cacheEntry->second;

  int id = glGetAttribLocation(mProgram, name.c_str());
  if (id == -1)
    LogShaderProgramW() << "Attribute could not be found: " << name;

  mAttributeCache.insert({name, id});
  return id;
}

void ShaderProgram::setUniform(std::string name, Vec4 vec) const
{
  setUniform(getUniformLocation(name), vec);
}

void ShaderProgram::setUniform(int id, Vec4 vec) const
{
  GL_CHECK(glUniform4f(id, vec.x, vec.y, vec.z, vec.w));
}

void ShaderProgram::setUniform(std::string name, const Mat4& matrix) const
{
  setUniform(getUniformLocation(name), matrix);
}

void ShaderProgram::setUniform(int id, const Mat4& matrix) const
{
  if (id >= 0)
    GL_CHECK(glUniformMatrix4fv(id, 1, GL_FALSE, glm::value_ptr(matrix)));
}

void ShaderProgram::bind() const
{
  GL_CHECK(glUseProgram(mProgram));
}

void ShaderProgram::unbind() const
{
  GL_CHECK(glUseProgram(0));
}

unsigned ShaderProgram::getId() const
{
  return mProgram;
}

} // namespace aw
