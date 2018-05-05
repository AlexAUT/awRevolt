#pragma once

#include <aw/graphics/core/shaderStage.hpp>

#include <aw/utils/math/matrix.hpp>
#include <aw/utils/math/vector.hpp>

#include <functional>
#include <unordered_map>
#include <vector>

namespace aw
{
class ShaderProgram
{
public:
  ShaderProgram() = default;
  ~ShaderProgram();

  ShaderProgram(const ShaderProgram&) = delete;
  ShaderProgram operator=(const ShaderProgram&) = delete;

  bool link(const ShaderStage& vertexShader, const ShaderStage& fragmentShader);
  bool link(const std::vector<std::reference_wrapper<const ShaderStage>>& shaderStages);

  int getUniformLocation(std::string name) const;
  int getAttributeLocation(std::string name) const;

  void setUniform(std::string name, Vec4 vec) const;
  void setUniform(int id, Vec4 vec) const;
  void setUniform(std::string name, const Mat4& matrix) const;
  void setUniform(int id, const Mat4& matrix) const;

  void bind() const;
  void unbind() const;

  unsigned getId() const;

private:
private:
  unsigned mProgram{0};

  mutable std::unordered_map<std::string, int> mUniformCache;
  mutable std::unordered_map<std::string, int> mAttributeCache;
};
} // namespace aw
