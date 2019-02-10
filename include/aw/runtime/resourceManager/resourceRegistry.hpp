#pragma once

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
  using TypePtr = std::shared_ptr<ResourceType>;
  using ConstTypePtr = std::shared_ptr<const ResourceType>;

public:
  ResourceRegistry() = default;
  ResourceRegistry(const ResourceRegistry&) = delete;
  ResourceRegistry operator=(const ResourceRegistry&) = delete;

  TypePtr insert(std::string name, TypePtr object);

  template <typename Factory, typename... Args>
  TypePtr emplace(std::string name, Args&&... args);

  template <typename... Args>
  TypePtr emplace(std::string name, Args&&... args);

  bool has(std::string_view name) const;
  TypePtr get(std::string_view name);
  ConstTypePtr get(std::string_view name) const;

private:
private:
  std::unordered_map<std::string, TypePtr> mRegistry;
};
} // namespace aw

#include <aw/runtime/resourceManager/resourceRegistry.inl>
