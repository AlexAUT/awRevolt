#pragma once

#include <aw/graphics/3d/material.hpp>
#include <aw/graphics/core/shaderProgram.hpp>
#include <aw/runtime/entitySystem/indirectComponentManager.hpp>

#include <memory>
#include <vector>

namespace aw::ecs::components
{
class Mesh;
class MeshRenderer
{
public:
  using MeshPtr = std::shared_ptr<Mesh>;
  using Manager = aw::ecs::IndirectComponentManager<MeshRenderer>;

public:
  std::shared_ptr<ShaderProgram> shader{MeshRenderer::getDefaultShader()};
  std::vector<Material> materials;

private:
  static std::shared_ptr<ShaderProgram> getDefaultShader();
  ;
};

} // namespace aw::ecs::components
