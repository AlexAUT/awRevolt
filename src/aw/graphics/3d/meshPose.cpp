#include <aw/graphics/3d/meshPose.hpp>

#include <aw/graphics/3d/mesh.hpp>
#include <aw/graphics/3d/meshAnimation.hpp>
#include <aw/graphics/3d/meshInstance.hpp>
#include <aw/graphics/3d/meshSkeleton.hpp>

#include <aw/utils/log.hpp>

#include <glm/gtc/matrix_transform.hpp>

#include <cmath>

template <class T>
size_t findInterpIndex(float tickTime, const std::vector<T>& container)
{
  assert(container.size() > 1);
  for (size_t i = 0; i < container.size() - 1; i++)
    if (tickTime < container[i + 1].time)
      return i;

  assert(false && "There is a error in the time container");
  return 0;
}

namespace aw
{
void MeshPose::setMeshInstance(MeshInstance* meshInstance)
{
  mMeshInstance = meshInstance;
}

void MeshPose::update(float deltaTime)
{
  mAnimationTime += deltaTime;
  const auto* animation = mMeshInstance->getAnimation();
  float timeInTicks = std::fmod(mAnimationTime * animation->getTicksPerSecond(), animation->getDuration());

  Mat4 identity(1.f);
  mTransIndex = 0;
  upadateBones(timeInTicks, mMeshInstance->getMesh().getSkeleton()->getRootNode(), identity);
}

void MeshPose::upadateBones(float timeTicks, const MeshSkeletonNode& bone, const Mat4& parentTransform)
{
  const auto* animation = mMeshInstance->getAnimation();
  auto animChannel = animation->getChannel(bone.name);
  Mat4 boneTransform;
  if (animChannel)
  {
    Vec3 translation = calculateInterpolatedPosition(timeTicks, *animChannel);
    Vec3 scale = calculateInterpolatedScale(timeTicks, *animChannel);
    Quaternion rotation = calculateInterpolatedRotation(timeTicks, *animChannel);

    auto rotMatrix = glm::mat4_cast(rotation);
    Mat4 id{1.f};
    auto scaleMatrix = glm::scale(id, scale);
    auto transMatrix = glm::translate(id, translation);
    boneTransform = transMatrix * rotMatrix * scaleMatrix;
  }
  else
    boneTransform = bone.transformation;
  // boneTransform = bone.transformation;
  Mat4 globalTransformation = parentTransform * boneTransform;
  mMeshInstance->setBoneTransformation(bone.name, globalTransformation);

  for (auto& child : bone.children)
    upadateBones(timeTicks, child, globalTransformation);
}

Vec3 MeshPose::calculateInterpolatedPosition(float ticksTime, const MeshAnimationChannel& channel)
{
  if (channel.posKeys.size() == 0)
    return {0, 0, 0};
  if (channel.posKeys.size() == 1 || channel.posKeys[0].time > ticksTime)
    return channel.posKeys[0].value;
  const size_t startIndex = findInterpIndex(ticksTime, channel.posKeys);
  const size_t endIndex = startIndex + 1;
  const float timeBetween = channel.posKeys[endIndex].time - channel.posKeys[startIndex].time;
  const float ratio = (ticksTime - channel.posKeys[startIndex].time) / timeBetween;
  assert(ratio >= 0 && ratio <= 1);
  auto diff = channel.posKeys[endIndex].value - channel.posKeys[startIndex].value;
  return channel.posKeys[startIndex].value + diff * ratio;
}

Vec3 MeshPose::calculateInterpolatedScale(float ticksTime, const MeshAnimationChannel& channel)
{
  if (channel.scaleKeys.size() == 0)
    return {1.f, 1.f, 1.f};
  if (channel.scaleKeys.size() == 1 || channel.scaleKeys[0].time > ticksTime)
    return channel.scaleKeys[0].value;

  const size_t startIndex = findInterpIndex(ticksTime, channel.scaleKeys);
  const size_t endIndex = startIndex + 1;
  const float timeBetween = channel.scaleKeys[endIndex].time - channel.scaleKeys[startIndex].time;
  const float ratio = (ticksTime - channel.scaleKeys[startIndex].time) / timeBetween;
  assert(ratio >= 0 && ratio <= 1);
  auto diff = channel.scaleKeys[endIndex].value - channel.scaleKeys[startIndex].value;
  return channel.scaleKeys[startIndex].value + diff * ratio;
}

Quaternion MeshPose::calculateInterpolatedRotation(float ticksTime, const MeshAnimationChannel& channel)
{
  if (channel.rotKeys.size() == 0)
    return {0.f, 0.f, 0.f, 1.f};
  if (channel.rotKeys.size() == 1 || channel.rotKeys[0].time > ticksTime)
    return channel.rotKeys[0].value;

  const size_t startIndex = findInterpIndex(ticksTime, channel.rotKeys);
  const size_t endIndex = startIndex + 1;
  const float timeBetween = channel.rotKeys[endIndex].time - channel.rotKeys[startIndex].time;
  const float ratio = (ticksTime - channel.rotKeys[startIndex].time) / timeBetween;
  assert(ratio >= 0 && ratio <= 1);
  return glm::normalize(glm::lerp(channel.rotKeys[startIndex].value, channel.rotKeys[endIndex].value, ratio));
}

} // namespace aw
