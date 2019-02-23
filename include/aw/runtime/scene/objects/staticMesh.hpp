#pragma once

#include <aw/runtime/resourceManager/resourcePtr.hpp>
#include <aw/runtime/scene/objects/material.hpp>
#include <aw/utils/math/vector.hpp>

#include <vector>

namespace aw
{
class StaticMesh
{
public:
  using Positions = std::vector<aw::Vec3>;
  using Normals = std::vector<aw::Vec3>;
  using Indices = std::vector<unsigned>;
  using UVs = std::vector<aw::Vec2>;

public:
  void setPositions(Positions&& positions);
  void setNormals(Normals&& normals);
  void setIndices(Indices&& indices);
  void addUvChannel(UVs&& uvs);
  void setMaterial(ResourcePtr<Material> material);

  const Positions& getPositions() const { return mPositions; }
  const Normals& getNormals() const { return mNormals; }
  const Indices& getIndices() const { return mIndices; }
  const std::vector<UVs> getUVChannels() const { return mUVChannels; }
  const ResourcePtr<Material>& getMaterial() const { return mMaterial; }

private:
private:
  Positions mPositions;
  Normals mNormals;
  Indices mIndices;

  std::vector<UVs> mUVChannels;

  ResourcePtr<Material> mMaterial;
};
} // namespace aw
