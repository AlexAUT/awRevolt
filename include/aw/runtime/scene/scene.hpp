#pragma once

#include <aw/runtime/entitySystem/entitySystem.hpp>
#include <aw/runtime/scene/sceneNode.hpp>

#include <aw/runtime/managers/meshManager.hpp>

namespace aw
{
// For now just a typedef, may be converted to a separate class in the future
class Scene : public SceneNode
{
public:
  virtual ~Scene() = default;

  MeshManager& getMeshManager() { return mMeshManager; }
  const MeshManager& getMeshManager() const { return mMeshManager; }

  aw::ecs::EntitySystem& getEntitySystem() { return mEntitySystem; };
  const aw::ecs::EntitySystem& getEntitySystem() const { return mEntitySystem; }

private:
  aw::ecs::EntitySystem mEntitySystem;

  MeshManager mMeshManager;
};
} // namespace aw
