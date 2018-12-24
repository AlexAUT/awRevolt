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

  inline Entity getEntity(EntityId id) const;

  template <typename... Components>
  ComponentsView<typename Components::Manager...> getView();

  template <typename... Components>
  ComponentsView<const typename Components::Manager...> getView() const;

  template <typename Component>
  typename Component::Manager* getManager();

  template <typename Component>
  const typename Component::Manager* getManager() const;

  template <typename Component>
  size_t getComponentCount() const;

  template <typename Component>
  uint32 getComponentId() const;

private:
  EntityContainer mEntities;
  FreeListQueue mFreeList;

  ComponentManagers mComponentManagers;
};

Entity EntitySystem::getEntity(EntityId id) const
{
  auto index = id.getIndex();
  if (index < mEntities.size())
    return mEntities[index];
  return Entity();
}

template <typename Component>
uint32 EntitySystem::getComponentId() const
{
  return Entity::ComponentIndexer::getId<Component>();
}

template <typename... Components>
ComponentsView<typename Components::Manager...> EntitySystem::getView()
{
  return ComponentsView<typename Components::Manager...>(getManager<Components>()...);
}

template <typename... Components>
ComponentsView<const typename Components::Manager...> EntitySystem::getView() const
{
  return ComponentsView<const typename Components::Manager...>(getManager<Components>()...);
}

template <typename Component>
typename Component::Manager* EntitySystem::getManager()
{
  return const_cast<typename Component::Manager*>(static_cast<const EntitySystem*>(this)->getManager<Component>());
}

template <typename Component>
const typename Component::Manager* EntitySystem::getManager() const
{
  auto index = Entity::ComponentIndexer::getId<Component>();
  if (index >= mComponentManagers.size())
    return nullptr;
  auto* m = mComponentManagers[index].get();
  return static_cast<const typename Component::Manager*>(m);
}

template <typename Component>
size_t EntitySystem::getComponentCount() const
{
  auto* manager = getManager<Component>();
  return manager ? manager->getSize() : 0;
}

} // namespace aw::ecs
