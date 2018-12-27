#pragma once

#include <cassert>
#include <unordered_map>
#include <vector>

#include <aw/runtime/entitySystem/componentManager.hpp>
#include <aw/runtime/entitySystem/componentRef.hpp>
#include <aw/runtime/entitySystem/entityId.hpp>
#include <aw/utils/types.hpp>

namespace aw::ecs
{
template <class Component>
class IndirectComponentManager : public ComponentManager
{
public:
  using ComponentType = Component;
  using ComponentId = std::tuple<EntityId, size_t>;
  using ComponentReference = ComponentRef<Component>;
  using ConstComponentReference = ComponentRef<const Component>;
  using IdComponentTuple = std::tuple<EntityId, Component>;

  using ComponentContainer = std::vector<IdComponentTuple>;
  using LinkContainer = std::unordered_map<EntityId::StorageType, size_t>;

  using Iterator = EntityId;

public:
  size_t getComponentCount() const;
  size_t getEntityCount() const;

  template <typename... Args>
  ComponentReference add(EntityId id, Args... args);

  bool remove(EntityId id);
  bool has(EntityId id) const;

  ComponentReference get(EntityId id);
  ConstComponentReference get(EntityId id) const;

  Component* get(ComponentId id);
  const Component* get(ComponentId id) const;

  Iterator begin() const;

  Iterator end() const;
  Iterator next(Iterator entityId) const;

  EntityId getEntityId(Iterator entityId) const;

private:
  LinkContainer mResolveTable;
  ComponentContainer mComponents;
};

template <class Component>
size_t IndirectComponentManager<Component>::getComponentCount() const
{
  assert(mResolveTable.size() == mComponents.size());
  return mResolveTable.size();
}

template <class Component>
size_t IndirectComponentManager<Component>::getEntityCount() const
{
  // No duplicates so componentCount == EntityCount
  return getComponentCount();
}

template <class Component>
template <typename... Args>
auto IndirectComponentManager<Component>::add(EntityId id, Args... args) -> ComponentReference
{
  assert(!has(id) && "This manager does not support multiple components for one entity!");

  auto index = mComponents.size();
  mComponents.push_back(std::make_tuple(id, Component{std::forward<Args>(args)...}));
  mResolveTable[id.getIndex()] = index;

  return {{id, index}, this};
}

template <class Component>
bool IndirectComponentManager<Component>::remove(EntityId id)
{
  if (has(id))
  {
    auto entityIndex = id.getIndex();
    auto componentIndex = mResolveTable[entityIndex];
    assert(entityIndex == std::get<0>(mComponents[componentIndex]).getIndex());
    if (componentIndex != mComponents.size() - 1)
    {
      // Swap with last element
      std::swap(mComponents[componentIndex], mComponents.back());
      mResolveTable[std::get<EntityId>(mComponents[componentIndex]).getIndex()] = componentIndex;
    }
    mComponents.pop_back();
    mResolveTable.erase(entityIndex);
    return true;
  }
  return false;
}
template <class Component>
bool IndirectComponentManager<Component>::has(EntityId id) const
{
  return mResolveTable.find(id.getIndex()) != mResolveTable.end();
}

template <class Component>
auto IndirectComponentManager<Component>::get(EntityId id) -> ComponentReference
{
  assert(has(id));
  auto index = id.getIndex();
  auto found = mResolveTable.find(id.getIndex());
  if (found != mResolveTable.end())
    return {{id, index}, this};
  return {};
}

template <class Component>
auto IndirectComponentManager<Component>::get(EntityId id) const -> ConstComponentReference
{
  assert(has(id));
  auto index = id.getIndex();
  auto found = mResolveTable.find(id.getIndex());
  // TODO: enable_if in compRef to remove const_cast
  if (found != mResolveTable.end())
    return {{id, index}, const_cast<IndirectComponentManager*>(this)};
  return {};
}

template <class Component>
Component* IndirectComponentManager<Component>::get(ComponentId id)
{
  return const_cast<Component*>(static_cast<const IndirectComponentManager*>(this)->get(id));
}

template <class Component>
const Component* IndirectComponentManager<Component>::get(ComponentId id) const
{
  auto componentIndex = std::get<std::size_t>(id);
  auto entityId = std::get<EntityId>(id);
  // Check if the cached direct index is still valid
  if (mComponents.size() > componentIndex && entityId == std::get<EntityId>(mComponents[componentIndex]))
    return &std::get<Component>(mComponents[componentIndex]);
  // Get the new location
  if (has(entityId))
  {
    auto found = mResolveTable.find(entityId.getIndex());
    if (found != mResolveTable.end())
      return &std::get<Component>(mComponents[found->second]);
  }

  return nullptr;
}

template <class Component>
auto IndirectComponentManager<Component>::begin() const -> Iterator
{
  if (mComponents.empty())
    return {};
  return std::get<EntityId>(mComponents[0]);
}

template <class Component>
auto IndirectComponentManager<Component>::end() const -> Iterator
{
  return {};
}

template <class Component>
auto IndirectComponentManager<Component>::next(Iterator entityId) const -> Iterator
{
  if (has(entityId))
  {
    auto found = mResolveTable.find(entityId.getIndex());
    if (found != mResolveTable.end())
    {
      auto index = found->second + 1u;
      if (index < mComponents.size())
      {
        return std::get<EntityId>(mComponents[index]);
      }
    }
  }
  return {};
}

template <class Component>
EntityId IndirectComponentManager<Component>::getEntityId(Iterator entityId) const
{
  return entityId;
}

} // namespace aw::ecs
