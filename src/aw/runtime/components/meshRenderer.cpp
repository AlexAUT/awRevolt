#include <aw/runtime/components/meshRenderer.hpp>

#include <aw/utils/file/path.hpp>

#include <iostream>

namespace aw::ecs::components
{
std::shared_ptr<ShaderProgram> loadDefaultShader()
{
  auto vShader = aw::ShaderStage::loadFromPath(aw::ShaderStage::Vertex, aw::createAssetPath("shaders/simple.vert"));
  auto fShader = aw::ShaderStage::loadFromPath(aw::ShaderStage::Fragment, aw::createAssetPath("shaders/mesh.frag"));
  assert(vShader && fShader);
  auto prog = std::make_shared<ShaderProgram>();
  prog->link(*vShader, *fShader);

  return prog;
}

std::shared_ptr<ShaderProgram> MeshRenderer::getDefaultShader()
{
  static std::shared_ptr<ShaderProgram> shader = loadDefaultShader();
  return shader;
}
} // namespace aw::ecs::components
