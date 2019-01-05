#pragma once

namespace aw::ecs
{
class EntitySystem;
}

namespace aw::ecs::systems
{
class TransformSystem
{
public:
  TransformSystem(EntitySystem& entitySystem);

  void update(float dt);

private:
  EntitySystem& mEntitySystem;
};
} // namespace aw::ecs::systems
