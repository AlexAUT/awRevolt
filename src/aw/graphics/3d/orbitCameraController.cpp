#include <aw/graphics/3d/orbitCameraController.hpp>

#include <aw/graphics/core/camera.hpp>

#include <aw/utils/math/constants.hpp>
using namespace aw::constantsF;

#include <algorithm>
#include <cmath>

#include <aw/utils/log.hpp>

namespace aw
{
OrbitCameraController::OrbitCameraController(aw::Camera* camera) : mCamera(camera) {}

void OrbitCameraController::setCamera(aw::Camera* camera)
{
  mCamera = camera;
}

void OrbitCameraController::setRotationHorizontal(float radians)
{
  mHorizontalRotation = radians;
}

void OrbitCameraController::setRotationVertical(float radians)
{
  mVerticalRotation = radians;
}

void OrbitCameraController::setDistanceToViewPoint(float units)
{
  mDistance = std::max(0.f, units);
}

void OrbitCameraController::setViewAtPoint(Vec3 point)
{
  mLookAt = point;
}

void OrbitCameraController::rotateHorizontal(float radians)
{
  mHorizontalRotation += radians;
}

void OrbitCameraController::rotateVertical(float radians)
{
  mVerticalRotation += radians;
}

void OrbitCameraController::zoom(float units)
{
  mDistance += units;
  mDistance = std::max(0.f, mDistance);
}

void OrbitCameraController::update(float delta)
{
  (void)delta;
  if (!mCamera)
    return;
  // Move camera to right point
  const float horiScale = (std::cos(mHorizontalRotation));

  const Vec3 camPos =
      mLookAt + Vec3{horiScale * std::sin(mVerticalRotation) * mDistance, std::sin(mHorizontalRotation) * mDistance,
                     horiScale * std::cos(mVerticalRotation) * mDistance};
  mCamera->setPosition(camPos);
  const Vec3 rotation{-mHorizontalRotation, mVerticalRotation, 0};
  mCamera->setRotationEuler(rotation);
}

float OrbitCameraController::getHorizontalRotation() const
{
  return mHorizontalRotation;
}

float OrbitCameraController::getVerticalRotation() const
{
  return mVerticalRotation;
}

float OrbitCameraController::getDistanceToViewPoint() const
{
  return mDistance;
}

} // namespace aw
