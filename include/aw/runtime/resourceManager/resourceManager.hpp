#pragma once

#include <aw/runtime/resourceManager/resourceDatabase.hpp>
#include <aw/runtime/resourceManager/resourceRegistry.hpp>
#include <aw/utils/typeHelper/typeCounter.hpp>

#include <memory>
#include <vector>

namespace aw
{
class ResourceManager
{
public:
  using RegistryPtr = std::unique_ptr<ResourceRegistryBase>;
  using TypeCounter = aw::TypeCounter<ResourceManager>;

public:
  ResourceManager(
      std::unique_ptr<ResourceDatabase> resourceDatabase = std::make_unique<ResourceDatabaseUnorderedMap>()) :
      mResourceDatabase(std::move(resourceDatabase))
  {
  }

  void clear() { clear(std::make_unique<ResourceDatabaseUnorderedMap>()); }
  void clear(std::unique_ptr<ResourceDatabase> resourceDatabase)
  {
    mRegistries.clear();
    mResourceDatabase = std::move(resourceDatabase);
  }

  template <typename ResourceType>
  ResourceRegistry<ResourceType>& getRegistry();

  template <typename ResourceType>
  const ResourceRegistry<ResourceType>& getRegistry() const;

  ResourceDatabase& getResouceDatabase() { return *mResourceDatabase; }
  const ResourceDatabase& getResouceDatabase() const { return *mResourceDatabase; }

private:
private:
  mutable std::unique_ptr<ResourceDatabase> mResourceDatabase;
  mutable std::vector<RegistryPtr> mRegistries;
};
} // namespace aw

#include <aw/runtime/resourceManager/resourceManager.inl>
