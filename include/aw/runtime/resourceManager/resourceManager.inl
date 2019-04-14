namespace aw
{
template <typename ResourceType>
ResourceRegistry<ResourceType>& ResourceManager::getRegistry()
{
  const auto& registry = static_cast<const ResourceManager*>(this)->getRegistry<ResourceType>();
  return const_cast<ResourceRegistry<ResourceType>&>(registry);
}

template <typename ResourceType>
const ResourceRegistry<ResourceType>& ResourceManager::getRegistry() const
{
  auto index = TypeCounter::getId<ResourceType>();

  if (mRegistries.size() <= index)
  {
    auto diff = 1 + index - mRegistries.size();
    mRegistries.reserve(mRegistries.size() + diff);
    while (diff--)
      mRegistries.push_back(nullptr);
  }
  if (!mRegistries[index])
    mRegistries[index].reset(new ResourceRegistry<ResourceType>(*mResourceDatabase));

  return static_cast<const ResourceRegistry<ResourceType>&>(*mRegistries[index]);
}
} // namespace aw
