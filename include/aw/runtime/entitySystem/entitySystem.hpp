#pragma once

#include <aw/runtime/entitySystem/componentIterator.hpp>
#include <aw/runtime/entitySystem/componentManager.hpp>
#include <aw/runtime/entitySystem/componentRef.hpp>
#include <aw/runtime/entitySystem/componentView.hpp>
#include <aw/runtime/entitySystem/entity.hpp>
#include <aw/runtime/entitySystem/multiComponentView.hpp>
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
  auto getView();

  template <typename Component>
  ComponentIterator<Component> getComponentIterator();

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
auto EntitySystem::getView()
{
  if constexpr (sizeof...(Components) == 1)
    return ComponentView<Components...>(getManager<Components>()...);
  else
    return MultiComponentView<Components...>({getManager<Components>()...});
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
  return manager ? manager->getComponentCount() : 0;
}

template <typename Component>
ComponentIterator<Component> EntitySystem::getComponentIterator()
{
  auto* manager = getManager<Component>();
  if (manager)
    return {this, manager->begin()};
  return {this, {}};
}
} // namespace aw::ecs
