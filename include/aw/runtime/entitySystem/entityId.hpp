#pragma once

#include <aw/utils/types.hpp>

#include <limits>

namespace aw
{
class EntityId
{
public:
  static constexpr int idBits = 24;
  static constexpr int versionBits = 8;
  static_assert((idBits + versionBits) == 32);

  static constexpr uint32 invalidId = (std::numeric_limits<uint32>::max() << versionBits) >> versionBits;
  static constexpr uint32 maxId = invalidId - 1;

public:
  EntityId() : mId{(invalidId << versionBits) >> versionBits} {}
  EntityId(uint32 id, uint32 version) : mId{id}, mVersion{version} {}

  uint32 getId() const { return mId; }
  uint32 getIdVersion() const { return mVersion; };

  bool isValid() const { return mId != invalidId; }

private:
  uint32 mId : idBits;
  uint32 mVersion : versionBits;
};
} // namespace aw
