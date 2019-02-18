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
  template <typename ResourceType>
  ResourceRegistry<ResourceType>& getRegistry();

  template <typename ResourceType>
  const ResourceRegistry<ResourceType>& getRegistry() const;

  ResourceDatabase& getResouceDatabse() { return mResourceDatabase; }
  const ResourceDatabase& getResouceDatabse() const { return mResourceDatabase; }

private:
private:
  mutable ResourceDatabase mResourceDatabase;
  mutable std::vector<RegistryPtr> mRegistries;
};
} // namespace aw

#include <aw/runtime/resourceManager/resourceManager.inl>
