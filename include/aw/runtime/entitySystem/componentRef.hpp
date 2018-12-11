#pragma once

#include <aw/utils/types.hpp>

namespace aw::ecs
{
template <typename Component>
class ComponentRef
{
public:
  using ComponentType = Component;
  using ComponentManager = typename Component::Manager;
  using ComponentId = typename ComponentManager::ComponentId;

public:
  ComponentRef() = default;
  ComponentRef(ComponentId id, ComponentManager* manager) : mId(id), mManager(manager) {}

  Component* get() const { return mManager ? mManager->get(mId) : nullptr; }
  Component* operator->() const { return get(); }
  Component& operator*() const { return *get(); }

  bool operator==(const ComponentRef& rhs) { return mId == rhs.mId && mManager == rhs.mManager; }
  explicit operator bool() const { return get(); }

private:
  ComponentId mId;
  ComponentManager* mManager{nullptr};
};
} // namespace aw::ecs
