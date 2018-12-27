#pragma once

#include <aw/runtime/entitySystem/componentRef.hpp>
#include <aw/runtime/entitySystem/entityId.hpp>

#include <tuple>

namespace aw::ecs
{
template <typename Component>
class ComponentIterator
{
public:
  using Manager = typename Component::Manager;
  using IdValueTuple = std::tuple<EntityId, ComponentRef<Component>>;

public:
  IdValueTuple operator*();
  ComponentIterator& operator++();

  constexpr operator bool() const;
  bool operator==(const ComponentIterator& rhs) { return mManager == rhs.mManager && mIterator == rhs.mIterator; }
  bool operator!=(const ComponentIterator& rhs) { return !(*this == rhs); }

private:
public:
  Manager* mManager;
  typename Manager::Iterator mIterator;
};

template <typename CompView>
auto ComponentIterator<CompView>::operator*() -> IdValueTuple
{
  return {mManager->getEntityId(mIterator), mManager->get(mIterator)};
}

template <typename CompView>
auto ComponentIterator<CompView>::operator++() -> ComponentIterator&
{
  mIterator = mManager->next(mIterator);
  return *this;
}

template <typename CompView>
constexpr ComponentIterator<CompView>::operator bool() const
{
  return mManager->getEntityId(mIterator).isValid();
}
} // namespace aw::ecs
