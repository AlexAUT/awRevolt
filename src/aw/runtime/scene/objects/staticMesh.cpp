#include <aw/runtime/scene/objects/staticMesh.hpp>

namespace aw
{
void StaticMesh::setPositions(Positions&& positions)
{
  mPositions = std::move(positions);
}

void StaticMesh::setNormals(Normals&& normals)
{
  mNormals = std::move(normals);
}

void StaticMesh::setIndices(Indices&& indices)
{
  mIndices = std::move(indices);
}

void StaticMesh::addUvChannel(UVs&& uvs)
{
  mUVChannels.push_back(std::move(uvs));
}

void StaticMesh::setMaterial(ResourcePtr<Material> material)
{
  mMaterial = std::move(material);
}

} // namespace aw
