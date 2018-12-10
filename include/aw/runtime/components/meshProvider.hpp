#pragma once

#include <aw/runtime/entitySystem/indirectComponentManager.hpp>

#include <memory>

namespace aw
{
class Mesh;
}

namespace aw::ecs::components
{
class MeshProvider
{
public:
  using ConstMeshPtr = std::shared_ptr<Mesh>;
  using Manager = aw::ecs::IndirectComponentManager<MeshProvider>;

  ConstMeshPtr mMesh;
};
} // namespace aw::ecs::components
