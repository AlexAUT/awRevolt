#include <aw/runtime/resourceManager/resourceRegistry.hpp>

namespace aw
{
template <typename ResourceType>
auto ResourceRegistry<ResourceType>::insert(ResourceId id, std::shared_ptr<ResourceType> object) -> ResourcePointer
{
  auto present = get(id);
  if (present)
    return present;

  auto created = mRegistry.insert({std::move(id), std::move(object)});
  return {id, created.second ? created.first->second : nullptr};
}

template <typename ResourceType>
auto ResourceRegistry<ResourceType>::insert(std::string name, std::shared_ptr<ResourceType> object) -> ResourcePointer
{
  auto present = mResourceDatabase.has(name);
  if (present)
  {
    auto id = mResourceDatabase.get(name);
    return insert(id, object);
  }

  auto newId = mResourceDatabase.newResource(name);
  return insert(newId, object);
}

template <typename ResourceType>
template <typename Factory, typename... Args>
auto ResourceRegistry<ResourceType>::emplace(Args&&... args) -> ResourcePointer
{
  ResourcePointer newObject = Factory{}.create(*this, std::forward<Args>(args)...);
  auto found = get(newObject.id);
  if (found)
    return found;

  // Insert will never fail here because we checked it above
  return insert(newObject.id, newObject.resource);
}

template <typename ResourceType>
template <typename... Args>
auto ResourceRegistry<ResourceType>::emplace(ResourceId name, Args&&... args) -> ResourcePointer
{
  auto present = get(name);
  if (present)
    return present;

  auto created = mRegistry.emplace(name, std::make_shared(std::forward<Args>(args)...));
  return created.second ? created.first->second : nullptr;
}

template <typename ResourceType>
bool ResourceRegistry<ResourceType>::has(ResourceId id) const
{
  return mRegistry.find(id) != mRegistry.end();
}

template <typename ResourceType>
auto ResourceRegistry<ResourceType>::get(ResourceId id) -> ResourcePointer
{
  auto found = mRegistry.find(id);
  if (found != mRegistry.end())
    return {id, found->second};
  return {0, nullptr};
}

template <typename ResourceType>
auto ResourceRegistry<ResourceType>::get(ResourceId id) const -> ConstResourcePointer
{
  auto found = mRegistry.find(id);
  if (found != mRegistry.end())
    return {id, found->second};
  return {0, nullptr};
}

template <typename ResourceType>
bool ResourceRegistry<ResourceType>::has(const std::string& name) const
{
  auto present = mResourceDatabase.has(name);
  if (!present)
    return false;

  auto id = mResourceDatabase.get(name);
  return has(id);
}

template <typename ResourceType>
auto ResourceRegistry<ResourceType>::get(const std::string& name) -> ResourcePointer
{
  if (!has(name))
    return nullptr;

  auto id = mResourceDatabase.get(name);
  return get(id);
}

template <typename ResourceType>
auto ResourceRegistry<ResourceType>::get(const std::string& name) const -> ConstResourcePointer
{
  if (!has(name))
    return {0, nullptr};

  auto id = mResourceDatabase.get(name);
  return get(id);
}

} // namespace aw
