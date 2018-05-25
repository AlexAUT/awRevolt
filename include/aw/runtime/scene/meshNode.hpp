#pragma once

#include <aw/runtime/scene/sceneNode.hpp>

#include <aw/graphics/3d/meshInstance.hpp>

namespace aw
{
class Mesh;

class MeshNode : public SceneNode
{
public:
  MeshNode(const Mesh& mesh);

  MeshInstance& meshInstance();
  const MeshInstance& meshInstance() const;

private:
private:
  MeshInstance mMeshInstance;
};
} // namespace aw
