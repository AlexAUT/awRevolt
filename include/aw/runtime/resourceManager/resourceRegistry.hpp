#pragma once

#include <aw/runtime/resourceManager/resourceDatabase.hpp>
#include <aw/runtime/resourceManager/resourceID.hpp>
#include <aw/runtime/resourceManager/resourcePtr.hpp>

#include <memory>
#include <unordered_map>

namespace aw
{
class ResourceRegistryBase
{
public:
  ResourceRegistryBase() = default;
  virtual ~ResourceRegistryBase() = default;
};

template <typename ResourceType>
class ResourceRegistry : public ResourceRegistryBase
{
public:
  using ResourcePointer = ResourcePtr<ResourceType>;
  using ConstResourcePointer = ConstResourcePtr<ResourceType>;

public:
  ResourceRegistry(ResourceDatabase& db) : mResourceDatabase{db} {};
  ResourceRegistry(const ResourceRegistry&) = delete;
  ResourceRegistry operator=(const ResourceRegistry&) = delete;

  ResourcePointer insert(ResourceId id, std::shared_ptr<ResourceType> object);
  ResourcePointer insert(std::string id, std::shared_ptr<ResourceType> object);

  template <typename Factory, typename... Args>
  ResourcePointer emplace(Args&&... args);

  template <typename... Args>
  ResourcePointer emplace(ResourceId name, Args&&... args);

  bool has(ResourceId id) const;
  ResourcePointer get(ResourceId id);
  ConstResourcePointer get(ResourceId id) const;

  bool has(const std::string& name) const;
  ResourcePointer get(const std::string& name);
  ConstResourcePointer get(const std::string& name) const;

private:
private:
  ResourceDatabase& mResourceDatabase;
  std::unordered_map<ResourceId, std::shared_ptr<ResourceType>> mRegistry;
};
} // namespace aw

#include <aw/runtime/resourceManager/resourceRegistry.inl>
