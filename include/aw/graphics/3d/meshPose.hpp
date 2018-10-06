#pragma once

#include <aw/utils/math/matrix.hpp>
#include <aw/utils/math/quaternion.hpp>
#include <aw/utils/math/vector.hpp>

#include <unordered_map>

namespace aw
{
class MeshInstance;
struct MeshAnimationChannel;
class MeshSkeletonNode;

class MeshPose
{
public:
  void setMeshInstance(MeshInstance* instance);
  void update(float deltaTime);

private:
  void upadateBones(float timeTicks, const MeshSkeletonNode& bone, const Mat4& parentTransform);

  Vec3 calculateInterpolatedPosition(float ticksTime, const MeshAnimationChannel& channel);
  Vec3 calculateInterpolatedScale(float ticksTime, const MeshAnimationChannel& channel);
  Quaternion calculateInterpolatedRotation(float ticksTime, const MeshAnimationChannel& channel);

private:
  float mAnimationTime{0.f};
  MeshInstance* mMeshInstance{nullptr};

  std::unordered_map<std::string, Mat4> mTransformations;
  unsigned mTransIndex;
};
} // namespace aw
