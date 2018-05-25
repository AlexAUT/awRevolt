#include <aw/runtime/scene/meshNode.hpp>

namespace aw
{
MeshNode::MeshNode(const aw::Mesh& mesh) : mMeshInstance(mesh)
{
}

MeshInstance& MeshNode::meshInstance()
{
  return mMeshInstance;
}

const MeshInstance& MeshNode::meshInstance() const
{
  return mMeshInstance;
}

} // namespace aw
