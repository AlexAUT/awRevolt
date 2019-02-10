#pragma once

#include <aw/graphics/core/renderer.hpp>

namespace aw
{
class Camera;
}

namespace aw::ecs
{
class EntitySystem;
}

namespace aw::ecs::systems
{
class MeshRendererSystem
{
public:
  MeshRendererSystem(EntitySystem& entitySystem);

  void update(float dt);
  void render(const Camera& camera);

private:
private:
  EntitySystem& mEntitySystem;

  Renderer mRenderer{PrimitiveType::Triangles, IndicesType::UnsignedInt};
};
} // namespace aw::ecs::systems
