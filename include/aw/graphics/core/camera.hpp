#pragma once

#include <aw/utils/math/matrix.hpp>
#include <aw/utils/math/quaternion.hpp>
#include <aw/utils/math/vector.hpp>
#include <aw/utils/spatial/ray.hpp>

namespace aw
{

class Camera
{
public:
  enum ProjectionType
  {
    Orthographic,
    Perspective,
    Custom
  };

public:
  static Camera createPerspective(float aspectRatio, float fieldOfView, float near = 0.1f, float far = 1000.f);
  static Camera createOrthograpic(float left, float right, float bottom, float top, float near = 0.0f,
                                  float far = 100.f);
  static Camera createFromCustomProjection(const Mat4& customProjection);

public:
  Vec3 projectVector(Vec3 vector) const;
  Vec4 projectVector(Vec4 vector) const;

  Vec3 projectVectorWorldSpace(Vec3 vector) const;
  Vec4 projectVectorWorldSpace(Vec4 vector) const;

  // Setter of properties
  void setProjectionType(ProjectionType type);

  void setNearPlane(float near);
  void setFarPlane(float far);
  void setAspectRatio(float aspectRatio);
  void setOrthoWidth(float orthoWidth);
  void setFieldOfView(float fieldOfView);
  void setCustomProjectionMatrix(const Mat4& customProjection);

  // Set view properties to fixed point
  void setPosition(Vec3 position);
  void setRotation(Quaternion quaternion);
  void setRotationEuler(Vec3 eulerAngles);

  // Set view properties by an offset
  void move(Vec3 offset);
  void rotate(Quaternion rotation);
  void rotateEuler(Vec3 rotation);

  // Getter of properties
  ProjectionType getProjectionType() const;

  float getNearPlane() const;
  float getFarPlane() const;
  float getAspectRatio() const;
  float getOrthoWidth() const;
  float getFieldOfView() const;
  Vec3 getViewDirection() const;
  Vec3 getUpDirection() const;
  Vec3 getLeftDirection() const;

  // [0,0] is left top corner
  Vec3 getPointOnNearPlane(Vec2 relPosition) const;
  Vec3 getPointOnFarPlane(Vec2 relPosition) const;
  Vec3 getPointInDistance(Vec2 relPosition, float distance) const;

  Ray createRayFromScreenspace(Vec2 relPosition) const;
  Ray createCenteredRay() const;

  Vec3 getPosition() const;
  Quaternion getRotation() const;
  Vec3 getRotationEuler() const;

  // Getter of matrices
  const Mat4& getViewMatrix() const;
  const Mat4& getProjectionMatrix() const;
  const Mat4& getVPMatrix() const;

private:
  inline void invalidViewCache();
  inline void invalidProjectionCache();

  void updateViewMatrix() const;
  void updateProjectioMatrix() const;
  void updateVPMatrix() const;

private:
  ProjectionType mProjectionType;

  float mAspectRatio;
  float mOrthoWidth;
  float mFieldOfView;

  float mNear;
  float mFar;

  Vec3 mPosition;
  Quaternion mRotation;

  // Mutable because of lazy updatings/caching
  mutable bool mViewDirty{true};
  mutable bool mProjectionDirty{true};
  mutable bool mViewProjectionDirty{true};
  mutable Mat4 mViewMatrix;
  mutable Mat4 mProjectionMatrix;
  mutable Mat4 mViewProjectionMatrix;
};

} // namespace aw
