#pragma once

#include <aw/graphics/3d/meshPose.hpp>
#include <aw/graphics/3d/transform.hpp>
#include <aw/graphics/core/renderer.hpp>

#include <aw/utils/math/vector.hpp>

#include <memory>
#include <vector>

namespace aw
{
class Mesh;
class MeshAnimation;
class ShaderProgram;

class MeshInstance
{
public:
  MeshInstance(const Mesh& mesh);

  void setAnimation(const MeshAnimation* animation);

  void update(float delta);
  void render(const ShaderProgram& shader) const;

  void setBoneTransformation(const std::string& name, const Mat4& transform);

  const Mesh& getMesh() const;
  const MeshAnimation* getAnimation() const;
  const MeshPose& getPose() const;

private:
private:
  const Mesh& mMesh;
  const MeshAnimation* mAnimation{nullptr};
  MeshPose mPose;

  std::vector<Mat4> mBoneTransforms;

  Renderer mRenderer;
};
} // namespace aw
