#pragma once

#include <aw/runtime/entitySystem/entity.hpp>
#include <aw/utils/types.hpp>

#include <queue>
#include <vector>

namespace aw
{
class EntitySystem
{
public:
  using EntityContainer = std::vector<Entity>;
  using FreeListQueue = std::queue<size_t>;

public:
  Entity createEntity();
  bool destroyEntity(Entity& entity);

  // Call this to avoid allocations during runtime, give a good upperbound estimate
  void reserve(size_t count);

private:
private:
  EntityContainer mEntities;
  FreeListQueue mFreeList;
};
} // namespace aw
