#include <aw/graphics/3d/transform.hpp>

#include <glm/gtc/matrix_transform.hpp>

namespace aw
{

void Transform::setOrigin(Vec3 origin)
{
  mOrigin = origin;
  mOffOrigin = mOrigin == Vec3(0.f, 0.f, 0.f);
  mTransformDirty = true;
}

void Transform::setPosition(Vec3 position)
{
  mPosition = position;
  mTransformDirty = true;
}

void Transform::setScale(Vec3 scale)
{
  mScale = scale;
  mTransformDirty = true;
}

void Transform::setRotation(Quaternion quat)
{
  mRotation = quat;
  mTransformDirty = true;
}

void Transform::setRotationEuler(Vec3 rotation)
{
  mRotation = Quaternion(rotation);
  mTransformDirty = true;
}

void Transform::moveOrigin(Vec3 offset)
{
  mOrigin += offset;
  mOffOrigin = mOrigin == Vec3(0.f, 0.f, 0.f);
  mTransformDirty = true;
}

void Transform::move(Vec3 offset)
{
  mPosition += offset;
  mTransformDirty = true;
}

void Transform::scale(Vec3 scale)
{
  mScale += scale;
  mTransformDirty = true;
}

void Transform::rotate(Quaternion quat)
{
  mRotation *= quat;
  mTransformDirty = true;
}

void Transform::rotateEuler(Vec3 rotation)
{
  rotate(Quaternion(rotation));
}

Vec3 Transform::getPosition() const
{
  return mPosition;
}

Vec3 Transform::getScale() const
{
  return mScale;
}

Quaternion Transform::getRotation() const
{
  return mRotation;
}

Vec3 Transform::getRotationEuler() const
{
  return glm::eulerAngles(mRotation);
}

const Mat4& Transform::getTransform() const
{
  if (mTransformDirty)
  {
    mTransform = Mat4(1.f);
    Mat4 originOffset = glm::translate(mTransform, -mOrigin);
    Mat4 scaling = glm::scale(mTransform, mScale);
    Mat4 rotation = glm::mat4_cast(mRotation);
    Mat4 translation = glm::translate(mTransform, mPosition);
    mTransform = translation * rotation * scaling * originOffset;
    mTransformDirty = false;
  }
  return mTransform;
}

} // namespace aw
