#pragma once

#include <aw/runtime/entitySystem/entitySystem.hpp>
#include <aw/runtime/resourceManager/resourceManager.hpp>

namespace aw
{
// For now just a typedef, may be converted to a separate class in the future
class Scene
{
public:
  virtual ~Scene() = default;

  ResourceManager& getResourceManager() { return mResourceManager; }
  const ResourceManager& getResourceManager() const { return mResourceManager; }

  aw::ecs::EntitySystem& getEntitySystem() { return mEntitySystem; };
  const aw::ecs::EntitySystem& getEntitySystem() const { return mEntitySystem; }

private:
  aw::ecs::EntitySystem mEntitySystem;

  ResourceManager mResourceManager;
};
} // namespace aw
