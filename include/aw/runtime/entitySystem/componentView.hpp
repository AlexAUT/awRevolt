#pragma once

#include <cassert>
#include <functional>
#include <tuple>

#include <aw/runtime/entitySystem/componentManager.hpp>
#include <aw/runtime/entitySystem/componentRef.hpp>
#include <aw/runtime/entitySystem/entity.hpp>
#include <aw/runtime/entitySystem/entityId.hpp>
#include <aw/utils/types.hpp>

namespace aw::ecs
{
template <class Func, std::size_t... Is>
constexpr void static_for_impl(Func&& f, std::index_sequence<Is...>)
{
  (f(std::integral_constant<std::size_t, Is>{}), ...);
}

template <size_t iterations, class Func>
constexpr void static_for(Func&& f)
{
  static_for_impl(std::forward<Func>(f), std::make_index_sequence<iterations>{});
}

template <typename... Components>
class ComponentsIterator
{
public:
  using ManagerArray = std::array<ComponentManager*, sizeof...(Components)>;
  using ComponentRefTuple = std::tuple<ComponentRef<Components>...>;
  using EntityIdComponentsTuple = std::tuple<EntityId, ComponentRef<Components>...>;

  explicit constexpr operator bool() const { return mEntityId.isValid(); }

  template <typename Component>
  constexpr ComponentRef<Component> getComponentRef(size_t index)
  {
    auto* m = static_cast<typename Component::Manager*>(mManagers[index]);
    return m->get(mEntityId);
  }

  template <typename Component, typename... Rest>
  constexpr auto getComponentsTuple(size_t index = 0)
  {
    if constexpr (sizeof...(Rest) > 0)
      return std::tuple_cat(std::make_tuple(getComponentRef<Component>(index)), getComponentsTuple<Rest...>(index + 1));
    else
      return std::make_tuple(getComponentRef<Component>(index));
  }

  EntityIdComponentsTuple operator*()
  {
    return std::tuple_cat(std::make_tuple(mEntityId), getComponentsTuple<Components...>());
  }

  ComponentsIterator operator++(int)
  {
    auto copy = *this;
    ++(*this);
    return copy;
  }

  ComponentsIterator& operator++()
  {
    mEntityId = mNextFunction(mEntityId);
    return *this;
  }

  bool operator==(const ComponentsIterator& rhs) { return (!(*this) && !rhs) || (mEntityId == rhs.mEntityId); }
  bool operator!=(const ComponentsIterator& rhs) { return !(*this == rhs); }

  ComponentsIterator(EntityId entityId, ManagerArray managers, std::function<EntityId(EntityId)> func = {})
      : mEntityId(entityId), mManagers(managers), mNextFunction(func)
  {
  }

private:
  EntityId mEntityId;
  ManagerArray mManagers;
  std::function<EntityId(EntityId)> mNextFunction;
};

template <typename... Components>
class ComponentsView
{
public:
  using ComponentTuple = std::tuple<Components...>;
  using ManagerArray = std::array<ComponentManager*, sizeof...(Components)>;

public:
  template <typename... Managers>
  ComponentsView(Managers... managers) : mManagers({std::forward<Managers>(managers)...})
  {
  }

  ComponentsIterator<Components...> begin();
  ComponentsIterator<Components...> end();

private:
private:
  ManagerArray mManagers;
};

template <typename... Components>
ComponentsIterator<Components...> ComponentsView<Components...>::begin()
{
  size_t minCount = std::numeric_limits<size_t>::max();
  size_t foundIndex = 0;
  EntityId id{};
  std::function<EntityId(EntityId)> nextFunction;
  // EntityId entity;
  static_for<std::tuple_size<std::tuple<Components...>>::value>([&](auto index) {
    using Component = typename std::tuple_element<index, std::tuple<Components...>>::type;
    auto* m = static_cast<typename Component::Manager*>(mManagers[index]);

    auto size = m ? m->getSize() : 0;
    if (size < minCount)
    {
      minCount = size;
      foundIndex = index;
      if (m && size > 0)
      {
        id = m->begin();
        nextFunction = [=](EntityId currentId) { return m->next(currentId); };
      }
      else
      {
        id = EntityId();
      }
    }
  });
  return ComponentsIterator<Components...>(id, mManagers, nextFunction);
} // namespace aw::ecs

template <typename... Components>
ComponentsIterator<Components...> ComponentsView<Components...>::end()
{
  return ComponentsIterator<Components...>(EntityId(), mManagers);
}
} // namespace aw::ecs
