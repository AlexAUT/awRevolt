#include <aw/runtime/entitySystem/entitySystem.hpp>

#include <cassert>

namespace aw::ecs
{
Entity EntitySystem::createEntity()
{
  if (mFreeList.empty())
  {
    assert(mEntities.size() < EntityId::maxIndex);
    mEntities.emplace_back(this, &mComponentManagers, mEntities.size(), 0);
    return mEntities.back();
  }
  else
  {
    auto index = mFreeList.front();
    mFreeList.pop();
    // Check for errors in the freelist
    assert(!mEntities[index].isValid());
    auto id = mEntities[index].getId();
    mEntities[index] = Entity(this, &mComponentManagers, id.getIndex(), id.getVersion() + 1);
    return mEntities[index];
  }
}

bool EntitySystem::destroyEntity(Entity& entity)
{
  auto entityIndex = entity.getId().getIndex();
  if (entity.isValid() && mEntities.size() > entityIndex && mEntities[entityIndex] == entity)
  {
    mEntities[entityIndex] = Entity();
    entity = Entity();
    return true;
  }
  return false;
}

void EntitySystem::reserve(size_t count)
{
  mEntities.reserve(count);
}

} // namespace aw::ecs
