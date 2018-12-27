#pragma once

#include <aw/runtime/entitySystem/componentIterator.hpp>

namespace aw::ecs
{
template <typename Component>
class ComponentView
{
public:
  using Manager = typename Component::Manager;
  using Iterator = ComponentIterator<Component>;

public:
  ComponentView() {}
  ComponentView(Manager* manager) : mManager(manager) {}

  Iterator begin();
  Iterator end();

private:
  Manager* mManager{nullptr};
};

template <typename Component>
auto ComponentView<Component>::begin() -> Iterator
{
  if (mManager)
    return {mManager, mManager->begin()};
  return {mManager, {}};
}

template <typename Component>
auto ComponentView<Component>::end() -> Iterator
{
  if (mManager)
    return {mManager, mManager->end()};
  return {mManager, {}};
}
} // namespace aw::ecs
