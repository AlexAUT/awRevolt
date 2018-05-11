#include <aw/graphics/3d/meshAnimation.hpp>

namespace aw
{
MeshAnimation::MeshAnimation(float duration, float ticksPerSecond, MeshAnimationChannels& channels)
    : mDuration(duration), mTicksPerSecond(ticksPerSecond), mChannels(channels)
{
}

float MeshAnimation::getDuration() const
{
  return mDuration;
}

float MeshAnimation::getTicksPerSecond() const
{
  return mTicksPerSecond;
}

size_t MeshAnimation::getNumChannels() const
{
  return mChannels.size();
}

const MeshAnimationChannel* MeshAnimation::getChannel(size_t index) const
{
  return index < getNumChannels() ? &mChannels[index] : nullptr;
}

const MeshAnimationChannel* MeshAnimation::getChannel(const std::string& boneName) const
{
  for (auto& channel : mChannels)
    if (channel.boneName == boneName)
      return &channel;
  return nullptr;
}

} // namespace aw
