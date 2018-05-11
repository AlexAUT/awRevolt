#include <aw/graphics/3d/meshInstance.hpp>

#include <aw/graphics/3d/mesh.hpp>
#include <aw/graphics/core/shaderProgram.hpp>

#include <aw/opengl/opengl.hpp>

namespace aw
{
MeshInstance::MeshInstance(const Mesh& mesh) : mMesh(mesh)
{
  mPose.setMeshInstance(this);
  mBoneTransforms.resize(mesh.getBoneCount());
}

void MeshInstance::setAnimation(std::shared_ptr<const MeshAnimation> animation)
{
  mAnimation = animation;
}

void MeshInstance::update(float delta)
{
  if (mAnimation && mMesh.getSkeleton())
    mPose.update(delta);
}

void MeshInstance::render(const ShaderProgram& shader)
{
  int bonesUniform = shader.getUniformLocation("bones[0]");
  if (bonesUniform >= 0)
  {
    shader.setUniformArrayMat4("bones[0]", mBoneTransforms.size(), reinterpret_cast<float*>(mBoneTransforms.data()));

    const unsigned meshCount = mMesh.getObjectCount();
    for (unsigned i = 0; i < meshCount; i++)
    {
      const auto& meshObject = mMesh.getObject(i);
      meshObject.vao.bind();
      const auto& material = mMesh.getMaterial(meshObject.materialIndex);
      material.getDiffuseSlot(0).texture2D->bind();
      GL_CHECK(glDrawElements(GL_TRIANGLES, meshObject.indices.size(), GL_UNSIGNED_INT, (void*)0));
    }
  }
}

void MeshInstance::setBoneTransformation(const std::string& name, const Mat4& transform)
{
  int boneIndex = mMesh.getBoneIndex(name);
  if (boneIndex >= 0)
  {
    mBoneTransforms[boneIndex] = mMesh.getGlobalInverseTransform() * transform * mMesh.getBoneOffset(name);
  }
}

const Mesh& MeshInstance::getMesh() const
{
  return mMesh;
}

const MeshAnimation* MeshInstance::getAnimation() const
{
  return mAnimation.get();
}

const MeshPose& MeshInstance::getPose() const
{
  return mPose;
}

} // namespace aw
