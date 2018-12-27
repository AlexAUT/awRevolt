#pragma once

#include <aw/runtime/entitySystem/componentRef.hpp>
#include <aw/runtime/entitySystem/entityId.hpp>
#include <aw/utils/typeHelper/staticForLoop.hpp>

#include <tuple>
#include <variant>

namespace aw::ecs
{
template <typename... Components>
class MultiComponentIterator
{
public:
  using IdValuesTuple = std::tuple<EntityId, ComponentRef<Components>...>;
  using Managers = std::tuple<typename Components::Manager*...>;
  using IteratorsVariant = std::variant<typename Components::Manager::Iterator...>;

public:
  MultiComponentIterator() = default;
  MultiComponentIterator(Managers managers, size_t managerToIterate);

  IdValuesTuple operator*();
  MultiComponentIterator& operator++();

  constexpr operator bool() const;
  bool operator==(const MultiComponentIterator& rhs);
  bool operator!=(const MultiComponentIterator& rhs);

private:
  bool isEntityIdValidForAllManagers() const;

public:
  Managers mManagers;
  size_t mManagerToIterate;
  IteratorsVariant mIterator;
  EntityId mCurrentId{};
};

template <typename... Components>
MultiComponentIterator<Components...>::MultiComponentIterator(Managers managers, size_t managerToIterate) :
    mManagers(managers),
    mManagerToIterate(managerToIterate)
{
  staticFor<sizeof...(Components)>([this](auto i) {
    if (i == mManagerToIterate)
    {
      // Check if manager != null, if so just return (mCurrentId is invalid so the iterator will be invalid)
      if (!std::get<i>(mManagers))
        return;

      mIterator = IteratorsVariant{std::in_place_index<i>, std::get<i>(mManagers)->begin()};
      mCurrentId = std::get<i>(mManagers)->getEntityId(std::get<i>(mIterator));

      while (mCurrentId.isValid() && !isEntityIdValidForAllManagers())
      {
        mIterator = IteratorsVariant{std::in_place_index<i>, std::get<i>(mManagers)->next(std::get<i>(mIterator))};
        mCurrentId = std::get<i>(mManagers)->getEntityId(std::get<i>(mIterator));
      }
    }
  });
}

template <typename... Components>
auto MultiComponentIterator<Components...>::operator*() -> IdValuesTuple
{
  IdValuesTuple result;
  std::get<0>(result) = mCurrentId;
  staticFor<sizeof...(Components)>([this, &result](auto i) {
    auto* manager = std::get<i>(mManagers);
    if (manager)
      std::get<(i + 1)>(result) = std::get<i>(mManagers)->get(mCurrentId);
    else
      std::get<(i + 1)>(result) = {};
  });
  return result;
}

template <typename... Components>
auto MultiComponentIterator<Components...>::operator++() -> MultiComponentIterator&
{
  if (!mCurrentId.isValid())
    return *this;

  staticFor<sizeof...(Components)>([this](auto i) {
    if (i == mManagerToIterate)
    {
      do
      {
        mIterator = IteratorsVariant{std::in_place_index<i>, std::get<i>(mManagers)->next(std::get<i>(mIterator))};
        mCurrentId = std::get<i>(mManagers)->getEntityId(std::get<i>(mIterator));
      } while (mCurrentId.isValid() && !isEntityIdValidForAllManagers());
    }
  });
  return *this;
}

template <typename... Components>
bool MultiComponentIterator<Components...>::isEntityIdValidForAllManagers() const
{
  bool result = true;
  staticFor<sizeof...(Components)>([this, &result](auto i) {
    if (!std::get<i>(mManagers)->has(mCurrentId))
      result = false;
  });
  return result;
}

template <typename... Components>
constexpr MultiComponentIterator<Components...>::operator bool() const
{
  return mCurrentId.isValid();
}

template <typename... Components>
bool MultiComponentIterator<Components...>::operator==(const MultiComponentIterator& rhs)
{
  // If the current ID is not valid it is not a valid iterator
  if (mCurrentId.isValid() != rhs.mCurrentId.isValid())
    return false;

  return mCurrentId.isValid() == rhs.mCurrentId.isValid();

  // Check if manager are the same
  bool result = true;
  staticFor<sizeof...(Components)>(
      [this, &rhs, &result](auto i) { result = result && std::get<i>(mManagers) == std::get<i>(rhs.mManagers); });
  return result;
}
template <typename... Components>
bool MultiComponentIterator<Components...>::operator!=(const MultiComponentIterator& rhs)
{
  return !(*this == rhs);
}
} // namespace aw::ecs
