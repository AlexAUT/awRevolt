#include <aw/graphics/3d/transform.hpp>

#include <glm/gtc/matrix_transform.hpp>

namespace aw
{
Transform::Transform(std::function<void()> listenerCallback) : mChangeListener(listenerCallback)
{
}
void Transform::setOrigin(Vec3 origin)
{
  mOrigin = origin;
  mOffOrigin = mOrigin == Vec3(0.f, 0.f, 0.f);
  invalidTransformCache();
}

void Transform::setPosition(Vec3 position)
{
  mPosition = position;
  invalidTransformCache();
}

void Transform::setScale(Vec3 scale)
{
  mScale = scale;
  invalidTransformCache();
}

void Transform::setRotation(Quaternion quat)
{
  mRotation = quat;
  invalidTransformCache();
}

void Transform::setRotationEuler(Vec3 rotation)
{
  mRotation = Quaternion(rotation);
  invalidTransformCache();
}

void Transform::moveOrigin(Vec3 offset)
{
  mOrigin += offset;
  mOffOrigin = mOrigin == Vec3(0.f, 0.f, 0.f);
  invalidTransformCache();
}

void Transform::move(Vec3 offset)
{
  mPosition += offset;
  invalidTransformCache();
}

void Transform::scale(Vec3 scale)
{
  mScale += scale;
  invalidTransformCache();
}

void Transform::rotate(Quaternion quat)
{
  mRotation *= quat;
  invalidTransformCache();
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
  if (mCachedTransformVersion != mVersion)
  {
    mTransform = Mat4(1.f);
    Mat4 originOffset = glm::translate(mTransform, -mOrigin);
    Mat4 scaling = glm::scale(mTransform, mScale);
    Mat4 rotation = glm::mat4_cast(mRotation);
    Mat4 translation = glm::translate(mTransform, mPosition);
    mTransform = translation * rotation * scaling * originOffset;
    mCachedTransformVersion = mVersion;
  }
  return mTransform;
}

unsigned Transform::getVersionNumber() const
{
  return mCachedTransformVersion;
}

void Transform::invalidTransformCache()
{
  mVersion++;
  if (mChangeListener)
    mChangeListener();
}

} // namespace aw
