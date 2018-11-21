#pragma once

#include <aw/runtime/entitySystem/componentManager.hpp>
#include <aw/runtime/entitySystem/componentRef.hpp>
#include <aw/runtime/entitySystem/entity.hpp>

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
  using ComponentContainer = std::vector<Component>;
  using FlagContainer = std::vector<bool>;
  using ComponentId = uint32;
  using ComponentReference = ComponentRef<Component>;
  using ConstComponentReference = ComponentRef<const Component>;

public:
  virtual ~DirectComponentManager() = default;

  size_t size() const { return mAliveObjects; }

  template <typename... Args>
  ComponentReference add(Entity e, Args... args)
  {
    auto index = e.getId().getIndex();
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

  bool remove(Entity e)
  {
    assert(mIdFlags.size() > e.getId().getIndex());
    bool ret = false;
    std::swap(mIdFlags[e.getId().getIndex()], ret);
    if (ret)
      mAliveObjects--;
    return ret;
  }

  bool has(Entity e) const
  {
    auto id = e.getId().getIndex();
    return mComponents.size() > id && mIdFlags[id];
  }

  ComponentReference get(Entity e)
  {
    auto id = e.getId().getIndex();
    if (mIdFlags[id])
      return {id, this};
    return {};
  }

  const ComponentReference get(Entity e) const
  {
    auto id = e.getId().getIndex();
    if (mIdFlags[id])
      return {id, this};
    return {};
  }

  ComponentReference get(EntityId id)
  {
    auto index = id.getIndex();
    if (mIdFlags[index])
      return {index, this};
    return {};
  }

  Component* get(ComponentId id)
  {
    if (mComponents.size() > id && mIdFlags[id])
      return &mComponents[id];
    return nullptr;
  }

  EntityId begin()
  {
    for (size_t i = 0; i < mIdFlags.size(); i++)
    {
      if (mIdFlags[i])
        return EntityId(i, 0);
    }
    return {};
    ;
  }

  EntityId next(EntityId entityId)
  {
    for (size_t i = entityId.getIndex() + 1; i < mIdFlags.size(); i++)
    {
      if (mIdFlags[i])
        return EntityId(i, 0);
    }
    return {};
  }

private:
private:
  ComponentContainer mComponents;
  FlagContainer mIdFlags;
  size_t mAliveObjects{0};
};
} // namespace aw::ecs
