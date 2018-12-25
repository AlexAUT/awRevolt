#include <aw/graphics/core/camera.hpp>

#include <aw/utils/log.hpp>
#include <aw/utils/math/constants.hpp>

#include <glm/gtc/matrix_access.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>

#include <algorithm>

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

Camera Camera::createFromCustomProjection(const Mat4& customProj)
{
  Camera camera;
  camera.setProjectionType(ProjectionType::Custom);
  camera.setCustomProjectionMatrix(customProj);

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

void Camera::setCustomProjectionMatrix(const Mat4& customProj)
{
  assert(mProjectionType == ProjectionType::Custom &&
         "You have to set custom projection first, because it will not be saved when switching back");

  mProjectionMatrix = customProj;
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

Vec3 Camera::getViewDirection() const
{
  return -glm::column(getViewMatrix(), 2);
}

Vec3 Camera::getUpDirection() const
{
  return glm::column(getViewMatrix(), 1);
}

Vec3 Camera::getLeftDirection() const
{
  return glm::column(getViewMatrix(), 0);
}

Vec3 Camera::getPointOnNearPlane(Vec2 relPosition) const
{
  return getPointInDistance(relPosition, mNear);
}

Vec3 Camera::getPointOnFarPlane(Vec2 relPosition) const
{
  return getPointInDistance(relPosition, mFar);
}

Vec3 Camera::getPointInDistance(Vec2 relPosition, float distance) const
{
  Vec3 point;
  if (mProjectionType == ProjectionType::Perspective)
  {
    float tanFov = glm::tan(mFieldOfView * 0.5f);
    float nearHalfHeight = tanFov * distance;
    float nearHalfWidth = nearHalfHeight * mAspectRatio;
    point = {-nearHalfWidth + relPosition.x * nearHalfWidth * 2.f,
             nearHalfHeight - relPosition.y * nearHalfHeight * 2.f, -distance};
  }
  else if (mProjectionType == ProjectionType::Orthographic)
  {
    auto orthoHeight = mOrthoWidth * (1.f / mFieldOfView);
    point = {relPosition.x * mOrthoWidth - mOrthoWidth * 0.5f, relPosition.y * orthoHeight - orthoHeight * 0.5f,
             distance};
  }

  return glm::inverse(getViewMatrix()) * aw::Vec4(point, 1.f);
}

Ray Camera::createRayFromScreenspace(Vec2 relPosition) const
{
  auto targetPoint = getPointOnFarPlane(relPosition);
  return {getPosition(), targetPoint - getPosition()};
}

Ray Camera::createCenteredRay() const
{
  return createRayFromScreenspace(Vec2{0.5f, 0.5f});
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

    Mat4 rotationMatrix = glm::mat4_cast(glm::inverse(mRotation));
    mViewMatrix = rotationMatrix * glm::translate(Mat4(1.f), -mPosition);
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
    else if (mProjectionType == Camera::Orthographic)
    {
      const float widthHalf = mOrthoWidth / 2.f;
      const float heightHalf = widthHalf / mAspectRatio;
      mProjectionMatrix = glm::ortho(-widthHalf, widthHalf, -heightHalf, heightHalf, mNear, mFar);
    }
    // Not for custom projection the matrix is set directly by the setter
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
