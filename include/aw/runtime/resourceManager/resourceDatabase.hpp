#pragma once

#include <aw/runtime/resourceManager/resourceID.hpp>
#include <aw/utils/file/path.hpp>

#include <unordered_map>

namespace aw
{
// Stores references to files, loopup for string as key is implement in O(n)! For ResourceId O(1+m) (hashmap,
// collisionchaining)
class ResourceDatabase
{
public:
  bool has(ResourceId id) const;
  bool has(const std::string& name) const;

  ResourceId newResource(std::string name);
  void set(ResourceId id, std::string name);

  const std::string& get(ResourceId id) const;
  ResourceId get(const std::string& name) const;

private:
private:
  std::unordered_map<ResourceId, std::string> mEntries;
  ResourceId mNewIdCounter{0};
};
} // namespace aw
