#include <aw/runtime/resourceManager/resourceRegistry.hpp>

namespace aw
{
template <typename ResourceType>
template <typename Factory, typename... Args>
auto ResourceRegistry<ResourceType>::create(std::string name, Args&&... args) -> TypePtr
{
  auto present = get(name);
  if (present)
    return present;

  auto created = mRegistry.emplace(name, Factory{}.create(std::forward<Args>(args)...));
  return created.second ? created.first->second : nullptr;
}

template <typename ResourceType>
bool ResourceRegistry<ResourceType>::has(std::string_view name) const
{
  return mRegistry.find(name.data()) != mRegistry.end();
}

template <typename ResourceType>
auto ResourceRegistry<ResourceType>::get(std::string_view name) -> TypePtr
{
  auto found = mRegistry.find(name.data());
  if (found != mRegistry.end())
    return found->second;
  return nullptr;
}

template <typename ResourceType>
auto ResourceRegistry<ResourceType>::get(std::string_view name) const -> ConstTypePtr
{
  auto found = mRegistry.find(name.data());
  if (found != mRegistry.end())
    return found->second;
  return nullptr;
}
} // namespace aw
