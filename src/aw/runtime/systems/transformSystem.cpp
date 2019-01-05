#include <aw/runtime/systems/transformSystem.hpp>

#include <aw/runtime/components/transform.hpp>
#include <aw/runtime/entitySystem/entitySystem.hpp>
#include <aw/utils/log.hpp>

using Transform = aw::ecs::components::Transform;

namespace aw::ecs::systems
{
TransformSystem::TransformSystem(EntitySystem& entitySystem) : mEntitySystem(entitySystem) {}

static int orderNumber = 0;

void ensureOrder(Transform::Manager* manager, EntityId id, ComponentRef<Transform> transform)
{
  for (auto child : transform->getChildren())
  {
    auto childTransform = child.get<Transform>();
    childTransform->invalidateHierarchy();
    if (!manager->isBefore(id, child.getId()))
    {
      manager->swapPositions(id, child.getId());
      orderNumber++;
    }
    ensureOrder(manager, child.getId(), childTransform);
  }
  transform->validateHierarchy();
}

void TransformSystem::update(float dt)
{
  // Check if order of components needs a update
  // This is called sparsely
  auto* manager = mEntitySystem.getManager<Transform>();
  auto view = mEntitySystem.getView<Transform>();
  orderNumber = 0;
  for (auto [id, transform] : view)
  {
    if (transform->isHierarchyDirty())
    {
      ensureOrder(manager, id, transform);
    }
  }
  if (orderNumber != 0)
    LogTemp() << "Reorders needed: " << orderNumber;
  // Propagate dirty bit
  int dirtyPropagationNeeded = 0;
  for (auto [id, transform] : view)
  {
    if (transform->getParent().isValid())
    {
      if (transform->getParent().get<Transform>()->isTransformDirty())
      {
        transform->invalidateTransformCache();
        dirtyPropagationNeeded++;
      }
    }
  }
  if (dirtyPropagationNeeded > 0)
    LogTemp() << "Dirty propagations needed: " << dirtyPropagationNeeded;
  // Update transforms
  int updatesNeeded = 0;
  for (auto [id, transform] : view)
  {
    if (transform->isTransformDirty())
      updatesNeeded++;
    transform->updateTransform();
  }
  if (updatesNeeded > 0)
    LogTemp() << "Updates needed: " << updatesNeeded;
}

} // namespace aw::ecs::systems
