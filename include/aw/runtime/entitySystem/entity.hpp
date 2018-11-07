#pragma once

#include <aw/runtime/entitySystem/componentManager.hpp>
#include <aw/runtime/entitySystem/componentRef.hpp>
#include <aw/runtime/entitySystem/entityId.hpp>
#include <aw/utils/typeHelper/typeCounter.hpp>
#include <aw/utils/types.hpp>

#include <cassert>
#include <limits>
#include <vector>

namespace aw
{
class EntitySystem;

class Entity
{
public:
  using ComponentManagers = std::vector<ComponentManager::UPtr>;
  using ComponentIndexer = aw::TypeCounter<struct Opaque, uint32>;

public:
  Entity() = default;
  Entity(EntitySystem* system, ComponentManagers* compManagers, uint32 id, uint32 version)
      : mEntitySystem{system}, mComponentManagers{compManagers}, mId{id, version}
  {
  }

  uint32 getId() const { return mId.getId(); }
  uint32 getIdVersion() const { return mId.getIdVersion(); };

  bool destroy();
  bool isValid() const { return mId.isValid() && mEntitySystem; }

  template <typename Component>
  inline bool has() const;

  template <typename Component>
  inline aw::ComponentRef<Component> get();

  template <typename Component>
  inline aw::ComponentRef<const Component> get() const;

  template <typename Component, typename... Args>
  inline ComponentRef<Component> assign(Args&&... args);

  template <typename Component>
  inline bool remove();

  inline bool operator==(Entity rhs) const;

private:
  template <typename Component>
  typename Component::Manager* getManager();

  template <typename Component>
  const typename Component::Manager* getManager() const;

  template <typename Component>
  typename Component::Manager* createManager();

private:
  EntitySystem* mEntitySystem{nullptr};
  ComponentManagers* mComponentManagers;
  EntityId mId;
};
} // namespace aw

namespace aw
{
template <typename Component>
bool Entity::has() const
{
  if (isValid())
  {
    auto* manager = getManager<Component>();
    if (manager)
      return manager->has(*this);
  }
  return false;
}

template <typename Component>
aw::ComponentRef<Component> Entity::get()
{
  if (isValid())
  {
    auto* manager = getManager<Component>();
    if (manager)
      return manager->get(*this);
  }
  return {};
}

template <typename Component>
aw::ComponentRef<const Component> Entity::get() const
{
  if (isValid())
  {
    auto* manager = getManager<Component>();
    if (manager)
      return manager->get(*this);
  }
  return {};
}

template <typename Component, typename... Args>
ComponentRef<Component> Entity::assign(Args&&... args)
{
  if (isValid())
  {
    auto* manager = getManager<Component>();
    if (!manager)
      manager = createManager<Component>();
    assert(manager);
    return manager->add(*this, std::forward<Args>(args)...);
  }
  return {};
}

template <typename Component>
typename Component::Manager* Entity::getManager()
{
  auto componentId = ComponentIndexer::getId<Component>();
  if (componentId >= mComponentManagers->size())
    return nullptr;
  auto* opaqueManager = (*mComponentManagers)[componentId].get();
  return static_cast<typename Component::Manager*>(opaqueManager);
}

template <typename Component>
const typename Component::Manager* Entity::getManager() const
{
  auto componentId = ComponentIndexer::getId<Component>();
  if (componentId >= mComponentManagers->size())
    return nullptr;
  auto* opaqueManager = (*mComponentManagers)[componentId].get();
  return static_cast<const typename Component::Manager*>(opaqueManager);
}

template <typename Component>
typename Component::Manager* Entity::createManager()
{
  auto componentId = ComponentIndexer::getId<Component>();
  if (componentId >= mComponentManagers->size())
    mComponentManagers->resize(componentId + 1);
  assert(!(*mComponentManagers)[componentId]);
  (*mComponentManagers)[componentId] = std::make_unique<typename Component::Manager>();
  return static_cast<typename Component::Manager*>((*mComponentManagers)[componentId].get());
}

template <typename Component>
inline bool Entity::remove()
{
  auto* manager = getManager<Component>();
  if (manager)
    return manager->remove(*this);
  return false;
}

bool Entity::operator==(Entity rhs) const
{
  return getId() == rhs.getId() && getIdVersion() == rhs.getIdVersion();
}
} // namespace aw
