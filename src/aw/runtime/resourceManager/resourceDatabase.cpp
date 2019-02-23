#include <aw/runtime/resourceManager/resourceDatabase.hpp>

#include <cassert>

std::string empty = "";

namespace aw
{
bool ResourceDatabase::has(ResourceId id) const
{
  return mEntries.find(id) != mEntries.end();
}

bool ResourceDatabase::has(const std::string& id) const
{
  for (auto& entry : mEntries)
  {
    if (entry.second == id)
      return true;
  }
  return false;
}

ResourceId ResourceDatabase::newResource(std::string name)
{
  auto tryInsert = [this, &name]() { return mEntries.try_emplace(mNewIdCounter++, name); };

  auto inserted = tryInsert();
  while (!inserted.second)
  {
    inserted = tryInsert();
  }

  return inserted.first->first;
}

void ResourceDatabase::set(ResourceId id, std::string name)
{
  mEntries.insert({id, name});
}

const std::string& ResourceDatabase::get(ResourceId id) const
{
  auto found = mEntries.find(id);
  if (found != mEntries.end())
    return found->second;

  assert(false && "Use has before get!");
  return empty;
}

ResourceId ResourceDatabase::get(const std::string& name) const
{
  for (auto& entry : mEntries)
  {
    if (entry.second == name)
      return entry.first;
  }

  assert(false && "Use has before get!");
  return 0;
}

} // namespace aw
