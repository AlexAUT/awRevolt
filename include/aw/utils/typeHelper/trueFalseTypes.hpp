#include <type_traits>

namespace aw
{
template <typename T>
struct AlwaysTrue : std::true_type
{
};
template <typename T>
struct AlwaysFalse : std::false_type
{
};
} // namespace aw
