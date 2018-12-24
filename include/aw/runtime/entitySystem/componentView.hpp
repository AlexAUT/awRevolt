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

template <typename... ComponentManagers>
class ComponentsIterator
{
public:
  using ManagerArray = std::array<const ComponentManager*, sizeof...(ComponentManagers)>;
  using ComponentRefTuple = std::tuple<ComponentRef<typename ComponentManagers::ComponentType>...>;
  using EntityIdComponentsTuple = std::tuple<EntityId, ComponentRef<typename ComponentManagers::ComponentType>...>;

  explicit constexpr operator bool() const { return mEntityId.isValid(); }

  template <typename Component>
  constexpr ComponentRef<Component> getComponentRef(size_t index)
  {
    auto* m =
        const_cast<typename Component::Manager*>(static_cast<const typename Component::Manager*>(mManagers[index]));
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
    return std::tuple_cat(std::make_tuple(mEntityId),
                          getComponentsTuple<typename ComponentManagers::ComponentType...>());
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

  ComponentsIterator(EntityId entityId, ManagerArray managers, std::function<EntityId(EntityId)> func = {}) :
      mEntityId(entityId),
      mManagers(managers),
      mNextFunction(func)
  {
  }

private:
  EntityId mEntityId;
  ManagerArray mManagers;
  std::function<EntityId(EntityId)> mNextFunction;
};

template <typename... ComponentManagers>
class ComponentsView
{
public:
  using ComponentTuple = std::tuple<typename ComponentManagers::ComponentType...>;
  using ManagerArray = std::array<const ComponentManager*, sizeof...(ComponentManagers)>;

public:
  ComponentsView(ComponentManagers*... managers) : mManagers({managers...}) {}

  ComponentsIterator<ComponentManagers...> begin();
  ComponentsIterator<ComponentManagers...> end();

private:
private:
  ManagerArray mManagers;
};

template <typename... ComponentManagers>
ComponentsIterator<ComponentManagers...> ComponentsView<ComponentManagers...>::begin()
{
  size_t minCount = std::numeric_limits<size_t>::max();
  size_t foundIndex = 0;
  EntityId id{};
  std::function<EntityId(EntityId)> nextFunction;
  // EntityId entity;
  static_for<std::tuple_size<std::tuple<typename ComponentManagers::ComponentType...>>::value>([&](auto index) {
    using ComponentManager = typename std::tuple_element<index, std::tuple<ComponentManagers...>>::type;
    auto* m = const_cast<ComponentManager*>(static_cast<const ComponentManager*>(mManagers[index]));

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
  return ComponentsIterator<ComponentManagers...>(id, mManagers, nextFunction);
} // namespace aw::ecs

template <typename... ComponentManagers>
ComponentsIterator<ComponentManagers...> ComponentsView<ComponentManagers...>::end()
{
  return ComponentsIterator<ComponentManagers...>(EntityId(), mManagers);
}
} // namespace aw::ecs
