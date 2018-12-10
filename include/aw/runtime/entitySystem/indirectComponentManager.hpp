#pragma once

#include <cassert>
#include <unordered_map>
#include <vector>

#include <aw/runtime/entitySystem/componentManager.hpp>
#include <aw/runtime/entitySystem/componentRef.hpp>
#include <aw/runtime/entitySystem/entity.hpp>
#include <aw/runtime/entitySystem/entityId.hpp>
#include <aw/utils/types.hpp>

namespace aw::ecs
{
template <class Component>
class IndirectComponentManager : public ComponentManager
{
public:
  using ComponentId = std::tuple<EntityId, size_t>;
  using ComponentReference = ComponentRef<Component>;
  using IdComponentTuple = std::tuple<EntityId, Component>;
  using ConstComponentReference = ComponentRef<const Component>;

  using ComponentContainer = std::vector<IdComponentTuple>;
  using LinkContainer = std::unordered_map<EntityId::StorageType, size_t>;

public:
  size_t size() const
  {
    assert(mResolveTable.size() == mComponents.size());
    return mResolveTable.size();
  }

  template <typename... Args>
  ComponentReference add(Entity e, Args... args)
  {
    assert(!has(e) && "This manager does not support multiple components for one entity!");

    auto index = mComponents.size();
    mComponents.push_back(std::make_tuple(e.getId(), Component{std::forward<Args>(args)...}));
    mResolveTable[e.getId().getIndex()] = index;

    return {{e.getId(), index}, this};
  }

  bool remove(Entity e)
  {
    if (has(e))
    {
      auto entityIndex = e.getId().getIndex();
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

  bool has(Entity e) const { return has(e.getId()); }
  bool has(EntityId id) const { return mResolveTable.find(id.getIndex()) != mResolveTable.end(); }

  ComponentReference get(Entity e) { return get(e.getId()); }

  const ComponentReference get(Entity e) const { return get(e.getId()); }

  ComponentReference get(EntityId id)
  {
    auto index = id.getIndex();
    auto found = mResolveTable.find(id.getIndex());
    if (found != mResolveTable.end())
      return {{id, index}, this};
    return {};
  }

  Component* get(ComponentId id)
  {
    auto componentIndex = std::get<std::size_t>(id);
    auto entityId = std::get<EntityId>(id);
    // Check if the cached direct index is still valid
    if (mComponents.size() > componentIndex && entityId == std::get<EntityId>(mComponents[componentIndex]))
      return &std::get<Component>(mComponents[componentIndex]);
    // Get the new location
    if (has(entityId))
      return &std::get<Component>(mComponents[mResolveTable[entityId.getIndex()]]);

    return nullptr;
  }

  EntityId begin()
  {
    if (mComponents.empty())
      return {};
    return std::get<EntityId>(mComponents[0]);
  }

  EntityId next(EntityId entityId)
  {
    if (has(entityId))
    {
      auto index = mResolveTable[entityId.getIndex()] + 1u;
      if (index < mComponents.size())
      {
        return std::get<EntityId>(mComponents[index]);
      }
    }
    return {};
  }

private:
  LinkContainer mResolveTable;
  ComponentContainer mComponents;
};
} // namespace aw::ecs
