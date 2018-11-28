#pragma once

#include <aw/runtime/entitySystem/componentManager.hpp>
#include <aw/runtime/entitySystem/componentRef.hpp>
#include <aw/runtime/entitySystem/componentView.hpp>
#include <aw/runtime/entitySystem/entity.hpp>
#include <aw/utils/typeHelper/typeCounter.hpp>
#include <aw/utils/types.hpp>

#include <queue>
#include <unordered_map>
#include <vector>

namespace aw::ecs
{
class EntitySystem
{
public:
  using EntityContainer = std::vector<Entity>;
  using FreeListQueue = std::queue<size_t>;
  using ComponentManagers = Entity::ComponentManagers;

public:
  Entity createEntity();
  bool destroyEntity(Entity& entity);

  // Call this to avoid allocations during runtime, give a good upperbound estimate
  void reserve(size_t count);

  template <typename... Components>
  ComponentsView<Components...> getView();

  template <typename Component>
  typename Component::Manager* getManager()
  {
    auto index = Entity::ComponentIndexer::getId<Component>();
    if (index >= mComponentManagers.size())
      return nullptr;
    auto* m = mComponentManagers[index].get();
    return static_cast<typename Component::Manager*>(m);
  }

  template <typename Component>
  uint32 getComponentId();

private:
  EntityContainer mEntities;
  FreeListQueue mFreeList;

  ComponentManagers mComponentManagers;
};

template <typename Component>
uint32 EntitySystem::getComponentId()
{
  return Entity::ComponentIndexer::getId<Component>();
}

template <typename... Components>
ComponentsView<Components...> EntitySystem::getView()
{
  return ComponentsView<Components...>(getManager<Components>()...);
}

} // namespace aw::ecs
