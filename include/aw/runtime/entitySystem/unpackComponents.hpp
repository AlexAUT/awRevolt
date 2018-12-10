#pragma once

#include <aw/runtime/entitySystem/componentRef.hpp>
#include <aw/utils/types.hpp>

#include <tuple>

namespace aw::ecs
{
namespace detail
{
template <typename... Types, size_t... Is>
std::tuple<Types*...> unpack(const std::tuple<ComponentRef<Types>...>& indirectAccess, std::index_sequence<Is...>)
{
  return std::make_tuple(std::get<Is>(indirectAccess).get()...);
}
} // namespace detail

template <typename... Types>
std::tuple<Types*...> unpack(const std::tuple<ComponentRef<Types>...>& indirectAccess)
{
  return detail::unpack(indirectAccess, std::make_index_sequence<sizeof...(Types)>{});
}
} // namespace aw::ecs
