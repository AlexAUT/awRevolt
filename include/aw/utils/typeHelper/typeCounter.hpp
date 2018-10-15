#pragma once

#include <aw/utils/types.hpp>

#include <atomic>
#include <type_traits>

namespace aw
{
template <typename Category, typename CounterType = size_t>
class TypeCounter
{
public:
  template <typename T>
  CounterType getId() const
  {
    return generateId<typename std::decay<T>::type>();
  }

private:
  template <typename T>
  CounterType generateId() const
  {
    static CounterType typeId = mCounter.fetch_add(1);
    return typeId;
  }

private:
  mutable std::atomic<CounterType> mCounter{0};
};
} // namespace aw
