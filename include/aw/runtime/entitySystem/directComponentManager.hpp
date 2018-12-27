#pragma once

#include <aw/runtime/entitySystem/componentIterator.hpp>
#include <aw/runtime/entitySystem/componentManager.hpp>
#include <aw/runtime/entitySystem/componentRef.hpp>
#include <aw/runtime/entitySystem/entityId.hpp>

#include <cassert>
#include <iostream>
#include <utility>
#include <vector>

namespace aw::ecs
{
template <typename Component>
class DirectComponentManager : public ComponentManager
{
public:
  using ComponentType = Component;
  using ComponentContainer = std::vector<Component>;
  using FlagContainer = std::vector<bool>;
  using ComponentId = uint32;
  using ComponentReference = ComponentRef<Component>;
  using ConstComponentReference = ComponentRef<const Component>;
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
private:
  ComponentContainer mComponents;
  FlagContainer mIdFlags;
  size_t mAliveObjects{0};
};

template <typename Component>
size_t DirectComponentManager<Component>::getComponentCount() const
{
  return mAliveObjects;
}

template <typename Component>
size_t DirectComponentManager<Component>::getEntityCount() const
{
  // No duplicates so componentCount == EntityCount
  return getComponentCount();
}

template <typename Component>
template <typename... Args>
auto DirectComponentManager<Component>::add(EntityId id, Args... args) -> ComponentReference
{
  auto index = id.getIndex();
  if (index >= mComponents.size())
  {
    mComponents.resize(index + 1);
    auto missingCount = 1 + index - mIdFlags.size();
    mIdFlags.insert(mIdFlags.end(), missingCount, false);
    assert(mComponents.size() == mIdFlags.size());
  }

  assert(!mIdFlags[index] && "This manager does not support multiple components for one entity!");

  mComponents[index] = Component{std::forward<Args>(args)...};
  mIdFlags[index] = true;

  mAliveObjects++;
  return {index, this};
}

template <typename Component>
bool DirectComponentManager<Component>::remove(EntityId id)
{
  assert(mIdFlags.size() > id.getIndex());
  bool ret = false;
  std::swap(mIdFlags[id.getIndex()], ret);
  if (ret)
    mAliveObjects--;
  return ret;
}

template <typename Component>
bool DirectComponentManager<Component>::has(EntityId id) const
{
  auto index = id.getIndex();
  return mComponents.size() > index && mIdFlags[index];
}

template <typename Component>
auto DirectComponentManager<Component>::get(EntityId id) -> ComponentReference
{
  assert(has(id));
  auto index = id.getIndex();
  if (id.isValid() && mIdFlags[index])
    return {index, this};
  return {};
}

template <typename Component>
auto DirectComponentManager<Component>::get(EntityId id) const -> ConstComponentReference
{
  assert(has(id));
  auto index = id.getIndex();
  if (mIdFlags[index])
    return {index, this};
  return {};
}

template <typename Component>
Component* DirectComponentManager<Component>::get(ComponentId id)
{
  return const_cast<Component*>(static_cast<const DirectComponentManager*>(this)->get(id));
}

template <typename Component>
const Component* DirectComponentManager<Component>::get(ComponentId id) const
{
  if (mComponents.size() > id && mIdFlags[id])
    return &mComponents[id];
  return nullptr;
}

template <typename Component>
auto DirectComponentManager<Component>::begin() const -> Iterator
{
  for (size_t i = 0; i < mIdFlags.size(); i++)
  {
    if (mIdFlags[i])
      return EntityId(i, 0);
  }
  return {};
}

template <typename Component>
auto DirectComponentManager<Component>::end() const -> Iterator
{
  return {};
}

template <typename Component>
auto DirectComponentManager<Component>::next(Iterator entityId) const -> Iterator
{
  for (size_t i = entityId.getIndex() + 1; i < mIdFlags.size(); i++)
  {
    if (mIdFlags[i])
      return EntityId(i, 0);
  }
  return {};
}

template <typename Component>
EntityId DirectComponentManager<Component>::getEntityId(Iterator entityId) const
{
  return entityId;
}
} // namespace aw::ecs
