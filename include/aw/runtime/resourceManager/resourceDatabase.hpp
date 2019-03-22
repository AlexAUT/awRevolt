#pragma once

#include <aw/runtime/resourceManager/resourceID.hpp>
#include <aw/utils/file/path.hpp>

#include <unordered_map>

namespace aw
{
// Stores references to files, lookup for string as key is implement in O(n)! For ResourceId O(1+m) (hashmap,
// collisionchaining)
class ResourceDatabase
{
public:
  virtual ~ResourceDatabase() = default;

  virtual bool has(ResourceId id) const = 0;
  virtual bool has(const std::string& name) const = 0;

  virtual ResourceId newResource(std::string name) = 0;
  virtual void set(ResourceId id, std::string name) = 0;

  virtual std::string get(ResourceId id) const = 0;
  virtual ResourceId get(const std::string& name) const = 0;
};

class ResourceDatabaseUnorderedMap final : public ResourceDatabase
{
public:
  virtual bool has(ResourceId id) const override;
  virtual bool has(const std::string& name) const override;

  virtual ResourceId newResource(std::string name) override;
  virtual void set(ResourceId id, std::string name) override;

  virtual std::string get(ResourceId id) const override;
  virtual ResourceId get(const std::string& name) const override;

private:
private:
  std::unordered_map<ResourceId, std::string> mEntries;
  ResourceId mNewIdCounter{0};
};
} // namespace aw
