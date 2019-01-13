#pragma once

#include <aw/graphics/3d/mesh.hpp>
#include <aw/runtime/resourceManager/resourceFactory.hpp>
#include <aw/utils/file/path.hpp>

namespace aw
{
class Path;
class ResourceManager;
} // namespace aw

namespace aw::factories
{
class MeshFactory : public ResourceFactory<MeshFactory, Mesh>
{
public:
  using TypePtr = std::shared_ptr<Mesh>;

public:
  TypePtr create(const aw::Path& path, ResourceManager& resourceManager);

private:
private:
};
} // namespace aw::factories

