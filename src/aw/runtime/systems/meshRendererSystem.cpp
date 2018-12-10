#include <aw/runtime/systems/meshRendererSystem.hpp>

#include <aw/graphics/3d/mesh.hpp>
#include <aw/graphics/core/camera.hpp>
#include <aw/runtime/components/meshProvider.hpp>
#include <aw/runtime/components/meshRenderer.hpp>
#include <aw/runtime/components/transform.hpp>
#include <aw/runtime/entitySystem/entitySystem.hpp>
#include <aw/runtime/entitySystem/unpackComponents.hpp>

#include <aw/opengl/opengl.hpp>

namespace aw::ecs::systems
{
MeshRendererSystem::MeshRendererSystem(EntitySystem& entitySystem) : mEntitySystem(entitySystem) {}

void MeshRendererSystem::update(float dt) {}

void MeshRendererSystem::render(const Camera& camera)
{
  glEnable(GL_DEPTH_TEST);
  glDisable(GL_STENCIL_TEST);
  glDisable(GL_BLEND);

  auto vp = camera.getVPMatrix();
  auto v = camera.getViewMatrix();

  using namespace aw::ecs::components;
  for (auto e : mEntitySystem.getView<Transform, MeshRenderer, MeshProvider>())
  {
    auto [transform, meshRenderer, meshProvider] = aw::ecs::unpack(e);

    assert(meshRenderer);
    auto* shader = meshRenderer->shader.get();
    assert(shader);

    shader->bind();
    shader->setUniform("has_bones", false);
    shader->setUniform("baseColor_tex", 0);
    shader->setUniform("decalColor_tex", 1);
    shader->setUniform("camera_position", camera.getPosition());
    shader->setUniform("camera_viewDir", glm::normalize(camera.getViewDirection()));
    shader->setUniform("vp_matrix", vp);

    shader->setUniform("mvp_matrix", vp * transform->getGlobalTransform());
    shader->setUniform("vm_matrix", v * transform->getGlobalTransform());
    shader->setUniform("m_matrix", transform->getGlobalTransform());

    auto* mesh = meshProvider->mMesh.get();
    const unsigned meshCount = static_cast<const unsigned>(mesh->getObjectCount());
    for (unsigned i = 0; i < meshCount; i++)
    {
      const auto& meshObject = mesh->getObject(i);
      meshObject.vao.bind();
      const auto& material = mesh->getMaterial(meshObject.materialIndex);
      shader->setUniform("diffuseColor", material.getDiffuseColor());
      shader->setUniform("ambientColor", material.getAmbientColor());
      shader->setUniform("specularColor", Vec4(material.getSpecularColor(), 10));
      shader->setUniform("enableDiffuseTex", material.getDiffseSlotCount() > 0);

      if (material.getDiffseSlotCount() > 0)
        material.getDiffuseSlot(0).texture2D->bind();
      shader->setUniform("enableDecalTex", material.getDiffseSlotCount() > 1);
      if (material.getDiffseSlotCount() > 1)
        material.getDiffuseSlot(1).texture2D->bind(1);
      mRenderer.renderElements(static_cast<int>(meshObject.indices.size()));
    }
  }
}
} // namespace aw::ecs::systems
