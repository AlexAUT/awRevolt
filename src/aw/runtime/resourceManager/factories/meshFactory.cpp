#include <aw/runtime/resourceManager/factories/meshFactory.hpp>

#include <aw/runtime/loaders/assimpLoader.hpp>

namespace aw::factories
{
auto MeshFactory::create(const aw::Path& path, ResourceManager& resourceManager) -> TypePtr
{
  AssimpLoader loader(resourceManager);
  loader.loadFromPath(path);

  auto meshUPtr = loader.loadMesh(path.getRelativePath());
  return TypePtr{meshUPtr.release()};
}

} // namespace aw::factories
