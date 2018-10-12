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
  CounterType getId()
  {
    return generateId<typename std::decay<T>::type>();
  }

private:
  template <typename T>
  CounterType generateId()
  {
    static CounterType typeId = mCounter.fetch_add(1);
    return typeId;
  }

private:
  std::atomic<CounterType> mCounter{0};
};
}
