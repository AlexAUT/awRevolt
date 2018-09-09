#include <aw/runtime/renderers/meshRenderer.hpp>

#include <aw/graphics/3d/directionalLight.hpp>
#include <aw/graphics/core/camera.hpp>
#include <aw/graphics/core/shaderProgram.hpp>
#include <aw/graphics/core/texture2D.hpp>

#include <aw/runtime/scene/meshNode.hpp>

#include <aw/utils/log.hpp>

namespace aw
{
void MeshRenderer::registerMesh(const MeshNode* meshNode)
{
  mMeshes.push_back(meshNode);
}

void MeshRenderer::renderShadowMap(const Camera& camera, const ShaderProgram& shader,
                                   const DirectionalLight& light) const
{
  aw::Vec3 inverseLight = -light.direction;

  auto vp = camera.getVPMatrix();
  auto v = camera.getViewMatrix();

  shader.bind();

  // Enable textures
  shader.setUniform("baseColor_tex", 0);
  // Set light information
  shader.setUniform("dirLights[0].dir", light.direction);
  shader.setUniform("dirLights[0].color", light.color);
  shader.setUniform("dirLights[0].energy", light.energy);

  for (auto meshNode : mMeshes)
  {
    shader.setUniform("mvp_matrix", vp * meshNode->getGlobalTransform());
    shader.setUniform("vp_matrix", vp);
    shader.setUniform("vm_matrix", v * meshNode->getGlobalTransform());
    shader.setUniform("m_matrix", meshNode->getGlobalTransform());
    meshNode->meshInstance().render(shader);
  }
}

void MeshRenderer::renderForwardPassWithShadow(const Camera& camera, const Camera& lightCam, const Texture2D& shadowMap,
                                               ShaderProgram& shader, const DirectionalLight& light) const
{
  shader.bind();

  const aw::Mat4 biasMatrix(0.5, 0.0, 0.0, 0.0, 0.0, 0.5, 0.0, 0.0, 0.0, 0.0, 0.5, 0.0, 0.5, 0.5, 0.5, 1.0);
  shader.setUniform("shadow_mvp_biased", biasMatrix * lightCam.getVPMatrix());

  shader.setUniform("dirLights[0].dir", light.direction);
  shader.setUniform("dirLights[0].color", light.color);
  shader.setUniform("dirLights[0].energy", light.energy);

  // Enable textures
  shader.setUniform("baseColor_tex", 0);
  shader.setUniform("decalColor_tex", 1);
  shader.setUniform("shadowMap_1", 2);
  shadowMap.bind(2);

  auto vp = camera.getVPMatrix();
  auto v = camera.getViewMatrix();
  for (auto meshNode : mMeshes)
  {
    shader.setUniform("mvp_matrix", vp * meshNode->getGlobalTransform());
    shader.setUniform("vp_matrix", vp);
    shader.setUniform("vm_matrix", v * meshNode->getGlobalTransform());
    shader.setUniform("m_matrix", meshNode->getGlobalTransform());
    meshNode->meshInstance().render(shader);
  }
}

void MeshRenderer::renderForwardPass(const Camera& camera, ShaderProgram& shader)
{
  shader.bind();

  auto vp = camera.getVPMatrix();
  auto v = camera.getViewMatrix();

  shader.setUniform("baseColor_tex", 0);
  shader.setUniform("decalColor_tex", 1);
  shader.setUniform("camera_position", camera.getPosition());
  shader.setUniform("camera_viewDir", glm::normalize(camera.getViewDirection()));
  shader.setUniform("vp_matrix", vp);
  for (auto meshNode : mMeshes)
  {
    shader.setUniform("mvp_matrix", vp * meshNode->getGlobalTransform());
    shader.setUniform("vm_matrix", v * meshNode->getGlobalTransform());
    shader.setUniform("m_matrix", meshNode->getGlobalTransform());
    meshNode->meshInstance().render(shader);
  }
}

} // namespace aw
