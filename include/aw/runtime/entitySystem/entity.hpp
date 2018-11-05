#pragma once

#include <aw/utils/types.hpp>

#include <limits>

namespace aw
{
class EntitySystem;

class Entity
{
public:
  static constexpr int idBits = 24;
  static constexpr int versionBits = 8;
  static_assert((idBits + versionBits) == 32);

  static constexpr uint32 invalidId = (std::numeric_limits<uint32>::max() << versionBits) >> versionBits;
  static constexpr uint32 maxId = invalidId - 1;

public:
  Entity() : mId{(invalidId << versionBits) >> versionBits} {}
  Entity(EntitySystem* system, uint32 id, uint32 version) : mEntitySystem{system}, mId{id}, mVersion{version} {}

  uint32 getId() const { return mId; }
  uint32 getIdVersion() const { return mVersion; };

  bool destroy();
  bool isValid() const { return mId != invalidId; }

  inline bool operator==(Entity rhs) const;

private:
  EntitySystem* mEntitySystem{nullptr};
  uint32 mId : idBits;
  uint32 mVersion : versionBits;
};

bool Entity::operator==(Entity rhs) const
{
  return getId() == rhs.getId() && getIdVersion() == rhs.getIdVersion();
}
} // namespace aw
