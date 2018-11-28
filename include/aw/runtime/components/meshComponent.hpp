#pragma once

#include <aw/runtime/entitySystem/indirectComponentManager.hpp>

#include <memory>

namespace aw
{
class Mesh;
class MeshComponent
{
public:
  using MeshPtr = std::shared_ptr<Mesh>;
  using Manager = aw::ecs::IndirectComponentManager<MeshComponent>;

  const std::shared_ptr<Mesh> mMesh;
};
} // namespace aw
