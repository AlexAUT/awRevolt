#pragma once

#include <aw/utils/math/quaternion.hpp>
#include <aw/utils/math/vector.hpp>
#include <aw/utils/types.hpp>

#include <string>
#include <vector>

namespace aw
{

struct VectorKey
{
  float time;
  Vec3 value;
};

struct QuaternionKey
{
  float time;
  Quaternion value;
};

struct MeshAnimationChannel
{
  std::string boneName;
  std::vector<VectorKey> posKeys;
  std::vector<VectorKey> scaleKeys;
  std::vector<QuaternionKey> rotKeys;
};
typedef std::vector<MeshAnimationChannel> MeshAnimationChannels;

class MeshAnimation
{
public:
  MeshAnimation(const std::string& fileName, const std::string& displayName, float duration, float ticksPerSecond,
                MeshAnimationChannels& channels);

  const std::string& getFileName() const;
  const std::string& getDisplayName() const;

  float getDuration() const;
  float getTicksPerSecond() const;
  size_t getNumChannels() const;
  const MeshAnimationChannel* getChannel(size_t index) const;
  const MeshAnimationChannel* getChannel(const std::string& boneName) const;

private:
private:
  const std::string mFileName;
  const std::string mDisplayName;
  const float mDuration;
  const float mTicksPerSecond;
  const MeshAnimationChannels mChannels;
};

} // namespace aw
