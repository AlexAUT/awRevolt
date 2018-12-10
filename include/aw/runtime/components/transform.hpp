#pragma once

#include <aw/runtime/entitySystem/directComponentManager.hpp>

#include <aw/utils/math/matrix.hpp>
#include <aw/utils/math/quaternion.hpp>
#include <aw/utils/math/vector.hpp>

namespace aw::ecs::components
{
class Transform
{
public:
  using Manager = aw::ecs::DirectComponentManager<Transform>;

public:
  Vec3 getPosition() const { return mPosition; }
  Vec3 getScale() const { return mScale; }
  Quaternion getRotiation() const { return mRotation; }
  const Mat4 getTransform() const { return Mat4{1.f}; }
  const Mat4 getGlobalTransform() const { return Mat4{1.f}; }

  inline void setPosition(Vec3 postion);
  inline void setScale(Vec3 scale);
  inline void setRotation(Quaternion rotation);

  inline void move(Vec3 offset);
  inline void scale(Vec3 scale);
  inline void rotate(Quaternion rotation);

public:
private:
  Vec3 mPosition{0.f};
  Vec3 mScale{1.f};
  Quaternion mRotation{0.f, 0.f, 0.f, 1.f};
  int mVersion{0};
};

void Transform::setPosition(Vec3 position)
{
  if (mPosition != position)
  {
    mPosition = position;
    mVersion++;
  }
}

void Transform::setScale(Vec3 scale)
{
  if (mScale != scale)
  {
    mScale = scale;
    mVersion++;
  }
}

void Transform::setRotation(Quaternion rotation)
{
  if (mRotation != rotation)
  {
    mRotation = rotation;
    mVersion++;
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

} // namespace aw::ecs::components
