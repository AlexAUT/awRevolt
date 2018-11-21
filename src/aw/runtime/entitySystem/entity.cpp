#include <aw/runtime/entitySystem/entity.hpp>

#include <aw/runtime/entitySystem/entitySystem.hpp>

#include <cassert>

namespace aw::ecs
{
bool Entity::destroy()
{
  if (isValid())
    return mEntitySystem->destroyEntity(*this);
  return false;
}
} // namespace aw::ecs
