#pragma once

#include <aw/utils/types.hpp>

#include <limits>

namespace aw::ecs
{
class EntityId
{
public:
  using StorageType = uint32;

  static constexpr int indexBits = 24;
  static constexpr int versionBits = 8;
  static_assert((indexBits + versionBits) == 32);

  static constexpr uint32 invalidIndex = (std::numeric_limits<uint32>::max() << versionBits) >> versionBits;
  static constexpr uint32 maxIndex = invalidIndex - 1;

public:
  EntityId() : mIndex{(invalidIndex << versionBits) >> versionBits}, mVersion{0} {}
  EntityId(uint32 index, uint32 version) : mIndex{index}, mVersion{version} {}

  StorageType getIndex() const { return mIndex; }
  StorageType getVersion() const { return mVersion; };

  bool isValid() const { return mIndex != invalidIndex; }

  bool operator==(const EntityId rhs) const { return mIndex == rhs.mIndex && mVersion == rhs.mVersion; }
  bool operator!=(const EntityId rhs) const { return mIndex != rhs.mIndex || mVersion != rhs.mVersion; }

  // To use it as key
  bool operator<(const EntityId rhs) const { return mIndex < rhs.mIndex; }

private:
  StorageType mIndex : indexBits;
  StorageType mVersion : versionBits;
};
} // namespace aw::ecs
