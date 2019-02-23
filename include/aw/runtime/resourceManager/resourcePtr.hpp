#pragma once

#include <memory>

#include <aw/runtime/resourceManager/resourceID.hpp>

namespace aw
{
template <typename Resource>
struct ResourcePtr
{
  ResourceId id;
  std::shared_ptr<Resource> resource;

  Resource* operator->() { return resource.get(); }
  const Resource* operator->() const { return resource.get(); }
  Resource& operator*() { return *resource; }
  const Resource& operator*() const { return *resource; }

  bool operator==(const ResourcePtr& rhs) const { return id == rhs.id && resource == rhs.resource; }
  explicit operator bool() const { return resource.get(); }
};

template <typename Resource>
struct ConstResourcePtr
{
  ResourceId id;
  std::shared_ptr<const Resource> resource;

  const Resource* operator->() const { return resource.get(); }
  const Resource& operator*() const { return *resource; }

  bool operator==(const ConstResourcePtr& rhs) const { return id == rhs.id && resource == rhs.resource; }
  explicit operator bool() const { return resource.get(); }
};
} // namespace aw
