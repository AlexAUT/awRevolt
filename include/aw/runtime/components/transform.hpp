#pragma once

#include <aw/runtime/entitySystem/entity.hpp>
#include <aw/runtime/entitySystem/entityId.hpp>
#include <aw/runtime/entitySystem/indirectComponentManager.hpp>

#include <aw/utils/math/matrix.hpp>
#include <aw/utils/math/quaternion.hpp>
#include <aw/utils/math/vector.hpp>

#include <algorithm>
#include <cassert>
#include <ostream>

namespace aw::ecs::components
{
class Transform
{
public:
  using Manager = aw::ecs::IndirectComponentManager<Transform>;

public:
  Transform() {}
  explicit Transform(Entity self) : mSelf(self) {}

  Entity getParent() const { return mParent; }
  const std::vector<Entity>& getChildren() const { return mChildren; }

  Vec3 getPosition() const { return mPosition; }
  Vec3 getScale() const { return mScale; }
  Quaternion getRotiation() const { return mRotation; }
  const Mat4& getLocalTransform() const { return mLocalTransform; }
  const Mat4& getGlobalTransform() const { return mGlobalTransform; }

  inline void setParent(Entity parent);

  inline void setPosition(Vec3 postion);
  inline void setScale(Vec3 scale);
  inline void setRotation(Quaternion rotation);

  inline void move(Vec3 offset);
  inline void scale(Vec3 scale);
  inline void rotate(Quaternion rotation);

  inline void invalidateTransformCache() { mIsTransformDirty = true; }
  bool isTransformDirty() const { return mIsTransformDirty; }
  inline void updateTransform();

  bool isHierarchyDirty() const { return mIsHierarchyDirty; }
  void validateHierarchy() { mIsHierarchyDirty = false; }
  inline void invalidateHierarchy();

private:
  inline void addChild(Entity child);

private:
  Entity mSelf{};
  Entity mParent{};
  std::vector<Entity> mChildren;

  Vec3 mPosition{0.f};
  Vec3 mScale{1.f};
  Quaternion mRotation{Vec3(0.f)};

  bool mIsTransformDirty{true};
  Mat4 mLocalTransform{1.f};
  Mat4 mGlobalTransform{1.f};

  bool mIsHierarchyDirty{false};
};

void Transform::setParent(Entity parent)
{
  if (mParent != parent)
  {
    mParent = parent;
    invalidateHierarchy();
    if (mParent.isValid())
      mParent.get<Transform>()->addChild(mSelf);
  }
}

void Transform::setPosition(Vec3 position)
{
  if (mPosition != position)
  {
    mPosition = position;
    invalidateTransformCache();
  }
}

void Transform::setScale(Vec3 scale)
{
  if (mScale != scale)
  {
    mScale = scale;
    invalidateTransformCache();
  }
}

void Transform::setRotation(Quaternion rotation)
{
  if (mRotation != rotation)
  {
    mRotation = rotation;
    invalidateTransformCache();
  }
}

void Transform::move(Vec3 offset)
{
  if (offset != Vec3{0.f})
    setPosition(mPosition + offset);
}

void Transform::scale(Vec3 scale)
{
  if (scale != Vec3{0.f})
    setScale(mScale + scale);
}

void Transform::rotate(Quaternion rotation)
{
  if (rotation.x != 0.f || rotation.y != 0.f || rotation.z != 0.f)
    setRotation(mRotation * rotation);
}

void Transform::invalidateHierarchy()
{
  invalidateTransformCache();
  mIsHierarchyDirty = true;
}

void Transform::updateTransform()
{
  mIsTransformDirty = false;

  Mat4 scaling = glm::scale(Mat4(1.f), mScale);
  Mat4 rotation = glm::mat4_cast(mRotation);
  Mat4 translation = glm::translate(Mat4(1.f), mPosition);
  mLocalTransform = translation * rotation * scaling;

  if (mParent.isValid())
    mGlobalTransform = mParent.get<Transform>()->getGlobalTransform() * mLocalTransform;
  else
    mGlobalTransform = mLocalTransform;
}

void Transform::addChild(Entity newChild)
{
  assert(std::all_of(mChildren.begin(), mChildren.end(), [newChild](const auto& child) { return newChild != child; }));
  invalidateHierarchy();
  mChildren.push_back(newChild);
}

} // namespace aw::ecs::components

std::ostream& operator<<(std::ostream& stream, const aw::ecs::components::Transform& transform);
