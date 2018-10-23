#pragma once

#include <aw/utils/math/vector.hpp>

namespace aw
{
class Camera;

class OrbitCameraController
{
public:
  OrbitCameraController() = default;
  explicit OrbitCameraController(aw::Camera* camera);

  void setCamera(aw::Camera* camera);

  void setRotationHorizontal(float radians);
  void setRotationVertical(float radians);
  void setDistanceToViewPoint(float units);
  void setViewAtPoint(Vec3 point);

  void rotateHorizontal(float radians);
  void rotateVertical(float radians);
  void zoom(float units);

  void update(float delta);

  float getHorizontalRotation() const;
  float getVerticalRotation() const;
  float getDistanceToViewPoint() const;

private:
private:
  aw::Camera* mCamera{nullptr};

  float mHorizontalRotation{0.f};
  float mVerticalRotation{0.f};
  float mDistance{2.f};
  Vec3 mLookAt{0.f};
};

} // namespace aw
