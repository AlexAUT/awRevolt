#pragma once

#include <aw/graphics/core/indicesBuffer.hpp>
#include <aw/graphics/core/vertex.hpp>
#include <aw/graphics/core/vertexArrayObject.hpp>
#include <aw/graphics/core/vertexBuffer.hpp>

#include <aw/graphics/3d/material.hpp>
#include <aw/graphics/3d/meshSkeleton.hpp>

#include <aw/utils/bBox.hpp>
#include <aw/utils/math/matrix.hpp>

#include <list>
#include <string>
#include <unordered_map>
#include <vector>

namespace aw
{

struct MeshObject
{
  std::string name;
  unsigned materialIndex;
  std::vector<VertexBones> vertices;
  std::vector<unsigned> indices;

  VertexBuffer vbo;
  IndicesBuffer ibo;
  VertexArrayObject vao;
};

struct MeshBone
{
  Mat4 offset;
};

class Mesh
{
public:
  Mesh(const std::string& fileName);
  Mesh(const std::string& fileName, const std::string& displayName);
  Mesh(const Mesh&) = delete;
  Mesh operator=(const Mesh&) = delete;

  void addObject(MeshObject* obj);
  void addMaterial(Material mat);

  const std::string& getFileName() const;
  const std::string& getDisplayName() const;

  size_t getObjectCount() const;
  const MeshObject& getObject(size_t index) const;

  size_t getMaterialCount() const;
  const Material& getMaterial(size_t index) const;

  int addBone(const std::string& name, const Mat4& offset);
  size_t getBoneCount() const;
  int getBoneIndex(const std::string& name) const;
  MeshBone* getMeshBone(const std::string& name);
  const Mat4& getBoneOffset(const std::string& name) const;

  void setSkeleton(std::shared_ptr<MeshSkeleton> skeleton);
  MeshSkeleton* getSkeleton() const;

  void setGlobalInverseTransform(const Mat4& mat);
  const Mat4& getGlobalInverseTransform() const;

  const BBox& getBounds() const;

private:
  std::string mFileName;
  std::string mDisplayName;

  std::vector<std::shared_ptr<MeshObject>> mObjects;
  std::vector<Material> mMaterials;

  Mat4 mGlobalInverseTranform;
  std::unordered_map<std::string, MeshBone> mBones;
  std::unordered_map<std::string, int> mBoneMapping;
  std::shared_ptr<MeshSkeleton> mSkeleton;

  BBox mBounds{0.f};
};

} // namespace aw
