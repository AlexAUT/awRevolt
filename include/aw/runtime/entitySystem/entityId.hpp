#pragma once

#include <aw/utils/types.hpp>

#include <limits>

namespace aw::ecs
{
class EntityId
{
public:
  static constexpr int indexBits = 24;
  static constexpr int versionBits = 8;
  static_assert((indexBits + versionBits) == 32);

  static constexpr uint32 invalidIndex = (std::numeric_limits<uint32>::max() << versionBits) >> versionBits;
  static constexpr uint32 maxIndex = invalidIndex - 1;

public:
  EntityId() : mIndex{(invalidIndex << versionBits) >> versionBits}, mVersion{0} {}
  EntityId(uint32 index, uint32 version) : mIndex{index}, mVersion{version} {}

  uint32 getIndex() const { return mIndex; }
  uint32 getVersion() const { return mVersion; };

  bool isValid() const { return mIndex != invalidIndex; }

  bool operator==(EntityId rhs) { return mIndex == rhs.mIndex && mVersion == rhs.mVersion; }

private:
  uint32 mIndex : indexBits;
  uint32 mVersion : versionBits;
};
} // namespace aw::ecs
