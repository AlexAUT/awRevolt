#include <type_traits>
template <typename... T>
struct voider
{
  using type = void;
};
template <typename... T>
using void_t = typename voider<T...>::type;

#define MEMBER_PRESENT_CHECKER(name, type)                                                                             \
  struct Just##name                                                                                                    \
  {                                                                                                                    \
    type name;                                                                                                         \
  };                                                                                                                   \
  template <typename T>                                                                                                \
  struct Multiple##name : public T, public Just##name                                                                  \
  {                                                                                                                    \
  };                                                                                                                   \
  template <typename T, typename = void>                                                                               \
  struct Has_##name : public std::true_type                                                                            \
  {                                                                                                                    \
  };                                                                                                                   \
  template <typename T>                                                                                                \
  struct Has_##name<T, void_t<decltype(Multiple##name<T>::name)>> : public std::false_type                             \
  {                                                                                                                    \
  };
