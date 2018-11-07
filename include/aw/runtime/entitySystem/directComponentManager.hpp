#pragma once

#include <aw/runtime/entitySystem/componentManager.hpp>
#include <aw/runtime/entitySystem/componentRef.hpp>
#include <aw/runtime/entitySystem/entity.hpp>

#include <cassert>
#include <utility>
#include <vector>

namespace aw
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

  template <typename... Args>
  ComponentReference add(Entity e, Args... args)
  {
    if (e.getId() >= mComponents.size())
    {
      mComponents.resize(e.getId() + 1);
      auto missingCount = 1 + e.getId() - mIdFlags.size();
      mIdFlags.assign(missingCount, false);
      assert(mComponents.size() == mIdFlags.size());
    }

    assert(!mIdFlags[e.getId()] && "This manager does not support multiple components for one entity!");

    mComponents[e.getId()] = Component{std::forward<Args>(args)...};
    mIdFlags[e.getId()] = true;

    return {e.getId(), this};
  }

  bool remove(Entity e)
  {
    assert(mIdFlags.size() > e.getId());
    bool ret = false;
    std::swap(mIdFlags[e.getId()], ret);
    return ret;
  }

  bool has(Entity e) const
  {
    auto id = e.getId();
    return mComponents.size() > id && mIdFlags[id];
  }

  ComponentReference get(Entity e)
  {
    auto id = e.getId();
    if (mIdFlags[id])
      return {id, this};
    return {};
  }

  const ComponentReference get(Entity e) const
  {
    auto id = e.getId();
    if (mIdFlags[id])
      return {id, this};
    return {};
  }

  Component* get(ComponentId id)
  {
    if (mComponents.size() > id && mIdFlags[id])
      return &mComponents[id];
    return nullptr;
  }

private:
private:
  ComponentContainer mComponents;
  FlagContainer mIdFlags;
};
} // namespace aw
