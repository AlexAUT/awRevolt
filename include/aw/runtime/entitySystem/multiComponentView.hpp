#pragma once

#include <aw/runtime/entitySystem/componentIterator.hpp>
#include <aw/runtime/entitySystem/componentView.hpp>
#include <aw/runtime/entitySystem/multiComponentIterator.hpp>
#include <aw/utils/typeHelper/staticForLoop.hpp>

#include <aw/utils/log.hpp>

#include <tuple>

namespace aw::ecs
{
template <typename... Components>
class MultiComponentView
{
public:
  using ManagerTuple = std::tuple<typename Components::Manager*...>;
  using ComponentViews = std::tuple<ComponentView<Components>...>;
  using Iterator = MultiComponentIterator<Components...>;

public:
  MultiComponentView(ManagerTuple managers);

  Iterator begin();
  Iterator end();

private:
private:
  ManagerTuple mManagers;
  ComponentViews mViews;

  size_t mManagerToIterate;
};

template <typename... Components>
MultiComponentView<Components...>::MultiComponentView(ManagerTuple managers) : mManagers{managers}
{
  constexpr auto count = sizeof...(Components);
  staticFor<count>([this](auto i) { std::get<i>(mViews) = {std::get<i>(mManagers)}; });

  // Search for manager with the least entities
  size_t lowest = std::numeric_limits<size_t>::max();
  staticFor<count>([this, &lowest](auto i) {
    auto* manager = std::get<i>(mManagers);
    if (!manager)
    {
      lowest = 0;
      mManagerToIterate = i;
      return;
    }
    auto count = manager->getEntityCount();
    if (count < lowest)
    {
      lowest = count;
      mManagerToIterate = i;
    }
  });
}

template <typename... Components>
auto MultiComponentView<Components...>::begin() -> Iterator
{
  return {mManagers, mManagerToIterate};
}
template <typename... Components>
auto MultiComponentView<Components...>::end() -> Iterator
{
  return {};
}
} // namespace aw::ecs
