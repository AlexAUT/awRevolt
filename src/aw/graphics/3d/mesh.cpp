#include <aw/graphics/3d/mesh.hpp>

#include <aw/utils/log.hpp>

namespace aw
{
Mesh::Mesh(const std::string& fileName) : Mesh(fileName, fileName)
{
}

Mesh::Mesh(const std::string& fileName, const std::string& displayName) : mFileName(fileName), mDisplayName(displayName)
{
}

void Mesh::addObject(MeshObject* obj)
{
  mObjects.emplace_back(obj);
}

void Mesh::addMaterial(Material mat)
{
  mMaterials.push_back(mat);
}

const std::string& Mesh::getFileName() const
{
  return mFileName;
}

const std::string& Mesh::getDisplayName() const
{
  return mDisplayName;
}

size_t Mesh::getObjectCount() const
{
  return mObjects.size();
}

const MeshObject& Mesh::getObject(size_t index) const
{
  return *mObjects[index];
}

size_t Mesh::getMaterialCount() const
{
  return mMaterials.size();
}

const Material& Mesh::getMaterial(size_t index) const
{
  return mMaterials[index];
}

int Mesh::addBone(const std::string& name, const Mat4& offset)
{
  mBones[name] = MeshBone{offset};
  mBoneMapping[name] = mBoneMapping.size();
  return mBoneMapping.size() - 1;
}

size_t Mesh::getBoneCount() const
{
  return mBones.size();
}

int Mesh::getBoneIndex(const std::string& name) const
{
  auto found = mBoneMapping.find(name);
  if (found != mBoneMapping.end())
    return found->second;
  return -1;
}

MeshBone* Mesh::getMeshBone(const std::string& name)
{
  auto found = mBones.find(name);
  if (found != mBones.end())
  {
    return &found->second;
  }
  return nullptr;
}

const Mat4& Mesh::getBoneOffset(const std::string& name) const
{
  assert(mBones.find(name) != mBones.end());
  return mBones.at(name).offset;
}

void Mesh::setSkeleton(std::shared_ptr<MeshSkeleton> skeleton)
{
  mSkeleton = skeleton;
}

MeshSkeleton* Mesh::getSkeleton() const
{
  return mSkeleton.get();
}

void Mesh::setGlobalInverseTransform(const Mat4& mat)
{
  mGlobalInverseTranform = mat;
}

const Mat4& Mesh::getGlobalInverseTransform() const
{
  return mGlobalInverseTranform;
}

} // namespace aw
