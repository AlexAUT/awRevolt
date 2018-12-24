#pragma once

#include <aw/utils/types.hpp>

#include <type_traits>

namespace aw::ecs
{
template <typename Component>
class ComponentRef
{
public:
  using ComponentType = Component;
  using ComponentManager = typename Component::Manager;
  using ConstComponentManager = const typename Component::Manager;
  using ComponentId = typename ComponentManager::ComponentId;

public:
  ComponentRef() = default;
  ComponentRef(ComponentId id, ComponentManager* manager) : mId(id), mManager(manager) {}

  Component* get() { return mManager ? mManager->get(mId) : nullptr; }
  const Component* get() const { return mManager ? mManager->get(mId) : nullptr; }

  Component* operator->() { return get(); }
  const Component* operator->() const { return get(); }
  Component& operator*() { return *get(); }
  const Component& operator*() const { return *get(); }

  bool operator==(const ComponentRef& rhs) { return mId == rhs.mId && mManager == rhs.mManager; }
  explicit operator bool() const { return get(); }

private:
  ComponentId mId;
  ComponentManager* mManager{nullptr};
};
} // namespace aw::ecs
