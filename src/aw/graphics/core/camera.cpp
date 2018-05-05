#include <aw/graphics/core/camera.hpp>

#include <aw/utils/math/constants.hpp>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>

namespace aw
{

Camera Camera::createPerspective(float aspectRatio, float fieldOfView, float near, float far)
{
  Camera camera;
  camera.setProjectionType(Camera::Perspective);
  camera.setAspectRatio(aspectRatio);
  camera.setFieldOfView(fieldOfView);
  camera.setNearPlane(near);
  camera.setFarPlane(far);
  return camera;
}

Camera Camera::createOrthograpic(float left, float right, float bottom, float top, float near, float far)
{
  Camera camera;
  camera.setProjectionType(Camera::Orthographic);

  const float orthoWidth = std::abs(right - left);
  const float orthoHeight = std::abs(bottom - top);
  camera.setAspectRatio(orthoWidth / orthoHeight);
  camera.setOrthoWidth(orthoWidth);
  camera.setNearPlane(near);
  camera.setFarPlane(far);

  Vec3 position{std::min(left, right) + orthoWidth / 2.f, std::min(bottom, top) + orthoHeight / 2.f, 1.f};
  camera.setPosition(position);

  return camera;
}

Vec3 Camera::projectVector(Vec3 vector) const
{
  return Vec3(projectVector(Vec4(vector, 1.f)));
}

Vec4 Camera::projectVector(Vec4 vector) const
{
  updateVPMatrix();
  return mViewProjectionMatrix * vector;
}

Vec3 Camera::projectVectorWorldSpace(Vec3 vector) const
{
  return Vec3(projectVectorWorldSpace(Vec4(vector, 1.f)));
}

Vec4 Camera::projectVectorWorldSpace(Vec4 vector) const
{
  updateViewMatrix();
  return mViewMatrix * vector;
}

void Camera::setProjectionType(Camera::ProjectionType type)
{
  mProjectionType = type;
  invalidProjectionCache();
}

void Camera::setNearPlane(float near)
{
  mNear = near;
  invalidProjectionCache();
}

void Camera::setFarPlane(float far)
{
  mFar = far;
  invalidProjectionCache();
}

void Camera::setAspectRatio(float aspectRatio)
{
  mAspectRatio = aspectRatio;
  invalidProjectionCache();
}

void Camera::setOrthoWidth(float orthoWidth)
{
  mOrthoWidth = orthoWidth;
  if (mProjectionType == ProjectionType::Orthographic)
    invalidProjectionCache();
}

void Camera::setFieldOfView(float fieldOfView)
{
  mFieldOfView = fieldOfView;
  if (mProjectionType == ProjectionType::Perspective)
    invalidProjectionCache();
}

void Camera::setPosition(Vec3 position)
{
  mPosition = position;
  invalidViewCache();
}

void Camera::setRotation(Quaternion quaternion)
{
  mRotation = quaternion;
  invalidViewCache();
}

void Camera::setRotationEuler(Vec3 eulerAngles)
{
  mRotation = glm::quat(eulerAngles);
  invalidViewCache();
}

void Camera::move(Vec3 offset)
{
  mPosition += offset;
  invalidViewCache();
}

void Camera::rotate(Quaternion rotation)
{
  mRotation = rotation * mRotation;
  invalidViewCache();
}

void Camera::rotateEuler(Vec3 rotation)
{
  mRotation *= glm::quat(rotation);
  invalidViewCache();
}

float Camera::getNearPlane() const
{
  return mNear;
}

float Camera::getFarPlane() const
{
  return mFar;
}

float Camera::getAspectRatio() const
{
  return mAspectRatio;
}

float Camera::getOrthoWidth() const
{
  return mOrthoWidth;
}

float Camera::getFieldOfView() const
{
  return mFieldOfView;
}

Vec3 Camera::getPosition() const
{
  return mPosition;
}

Quaternion Camera::getRotation() const
{
  return mRotation;
}

Vec3 Camera::getRotationEuler() const
{
  return glm::eulerAngles(mRotation);
}

const Mat4& Camera::getViewMatrix() const
{
  updateViewMatrix();
  return mViewMatrix;
}

const Mat4& Camera::getProjectionMatrix() const
{
  updateProjectioMatrix();
  return mProjectionMatrix;
}

const Mat4& Camera::getVPMatrix() const
{
  updateVPMatrix();
  return mViewProjectionMatrix;
}

void Camera::invalidViewCache()
{
  mViewDirty = true;
  mViewProjectionDirty = true;
}

void Camera::invalidProjectionCache()
{
  mProjectionDirty = true;
  mViewProjectionDirty = true;
}

void Camera::updateViewMatrix() const
{
  if (mViewDirty)
  {
    mViewDirty = false;

    Mat4 rotationMatrix = glm::mat4_cast(mRotation);
    mViewMatrix = glm::translate(rotationMatrix, -mPosition);
  }
}

void Camera::updateProjectioMatrix() const
{
  if (mProjectionDirty)
  {
    mProjectionDirty = false;
    if (mProjectionType == Camera::Perspective)
    {
      mProjectionMatrix = glm::perspective(mFieldOfView, mAspectRatio, mNear, mFar);
    }
    else
    {
      const float widthHalf = mOrthoWidth / 2.f;
      const float heightHalf = widthHalf / mAspectRatio;
      mProjectionMatrix = glm::ortho(-widthHalf, widthHalf, -heightHalf, heightHalf, mNear, mFar);
    }
  }
}

void Camera::updateVPMatrix() const
{
  if (mViewProjectionDirty)
  {
    mViewProjectionDirty = false;
    updateViewMatrix();
    updateProjectioMatrix();
    mViewProjectionMatrix = mProjectionMatrix * mViewMatrix;
  }
}

} // namespace aw
