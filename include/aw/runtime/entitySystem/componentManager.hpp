#pragma once

#include <memory>

namespace aw
{
/* Childs should implement:
Component* create(uint32 id);
Component* create(uint32 id, Component component);
Component* get(uint32 id) const;
*/

class EntitySystem;

class ComponentManager
{
public:
  using UPtr = std::unique_ptr<ComponentManager>;

public:
  virtual ~ComponentManager() = default;
};
} // namespace aw
