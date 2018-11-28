#include <aw/runtime/entitySystem/directComponentManager.hpp>
#include <aw/runtime/entitySystem/indirectComponentManager.hpp>

struct TransformIndirectManaged
{
  float x, y;

  bool operator==(const TransformIndirectManaged& rhs) const { return x == rhs.x && y == rhs.y; }

  using Manager = aw::ecs::IndirectComponentManager<TransformIndirectManaged>;
};

struct TransformDirectManaged
{
  float x, y;

  bool operator==(const TransformDirectManaged& rhs) const { return x == rhs.x && y == rhs.y; }

  using Manager = aw::ecs::IndirectComponentManager<TransformDirectManaged>;
};

struct MotionIndirectManaged
{
  float vX, vY;

  bool operator==(const MotionIndirectManaged& rhs) const { return vX == rhs.vX && vY == rhs.vY; }

  using Manager = aw::ecs::DirectComponentManager<MotionIndirectManaged>;
};

struct MotionDirectManaged
{
  float vX, vY;

  bool operator==(const MotionDirectManaged& rhs) const { return vX == rhs.vX && vY == rhs.vY; }

  using Manager = aw::ecs::DirectComponentManager<MotionDirectManaged>;
};
