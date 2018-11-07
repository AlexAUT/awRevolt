#include <aw/runtime/entitySystem/entitySystem.hpp>

#include <cassert>

namespace aw
{
Entity EntitySystem::createEntity()
{
  if (mFreeList.empty())
  {
    assert(mEntities.size() < EntityId::maxId);
    mEntities.emplace_back(this, &mComponentManagers, mEntities.size(), 0);
    return mEntities.back();
  }
  else
  {
    auto index = mFreeList.front();
    mFreeList.pop();
    // Check for errors in the freelist
    assert(!mEntities[index].isValid());
    mEntities[index] = Entity(this, &mComponentManagers, mEntities[index].getId(), mEntities[index].getIdVersion() + 1);
    return mEntities[index];
  }
}

bool EntitySystem::destroyEntity(Entity& entity)
{
  auto id = entity.getId();
  if (entity.isValid() && mEntities.size() > id && mEntities[id] == entity)
  {
    mEntities[id] = Entity();
    entity = Entity();
    return true;
  }
  return false;
}

void EntitySystem::reserve(size_t count)
{
  mEntities.reserve(count);
}

} // namespace aw
