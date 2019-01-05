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
  using Iterator = typename ComponentManager::Iterator;

public:
  ComponentRef() = default;
  ComponentRef(Iterator it, ComponentManager* manager) : mIterator(it), mManager(manager) {}

  Component* get() { return mManager ? mManager->getComponentPtr(mIterator) : nullptr; }
  const Component* get() const { return mManager ? mManager->getComponentPtr(mIterator) : nullptr; }

  Component* operator->() { return get(); }
  const Component* operator->() const { return get(); }
  Component& operator*() { return *get(); }
  const Component& operator*() const { return *get(); }

  bool operator==(const ComponentRef& rhs) { return mIterator == rhs.mId && mManager == rhs.mManager; }
  explicit operator bool() const { return get(); }

  Iterator getIterator() const { return mIterator; }

private:
  Iterator mIterator;
  ComponentManager* mManager{nullptr};
};

template <typename Component>
class ConstComponentRef
{
public:
  using ComponentType = Component;
  using ConstComponentManager = const typename Component::Manager;
  using Iterator = typename ConstComponentManager::Iterator;

public:
  ConstComponentRef() = default;
  ConstComponentRef(Iterator it, ConstComponentManager* manager) : mIterator(it), mManager(manager) {}

  Component* get() { return mManager ? mManager->getComponentPtr(mIterator) : nullptr; }
  const Component* get() const { return mManager ? mManager->getComponentPtr(mIterator) : nullptr; }

  const Component* operator->() const { return get(); }
  const Component& operator*() const { return *get(); }

  bool operator==(const ConstComponentRef& rhs) { return mIterator == rhs.mId && mManager == rhs.mManager; }
  explicit operator bool() const { return get(); }

  Iterator getIterator() const { return mIterator; }

private:
  Iterator mIterator;
  ConstComponentManager* mManager{nullptr};
};
} // namespace aw::ecs
