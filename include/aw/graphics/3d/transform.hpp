#pragma once

#include <aw/utils/math/matrix.hpp>
#include <aw/utils/math/quaternion.hpp>
#include <aw/utils/math/vector.hpp>

namespace aw
{
class Transform
{
public:
  void setOrigin(Vec3 origin);
  void setPosition(Vec3 position);
  void setScale(Vec3 scale);
  void setRotation(Quaternion quat);
  void setRotationEuler(Vec3 rotation);

  void moveOrigin(Vec3 offset);
  void move(Vec3 offset);
  void scale(Vec3 scale);
  void rotate(Quaternion quat);
  void rotateEuler(Vec3 rotation);

  Vec3 getOrigin() const;
  Vec3 getPosition() const;
  Vec3 getScale() const;
  Quaternion getRotation() const;
  Vec3 getRotationEuler() const;

  const Mat4& getTransform() const;

private:
private:
  bool mOffOrigin{false};
  Vec3 mOrigin{0.f, 0.f, 0.f};
  Vec3 mPosition{0.f, 0.f, 0.f};
  Vec3 mScale{1.f, 1.f, 1.f};
  Quaternion mRotation{0.f, 0.f, 0.f, 0.f};

  mutable bool mTransformDirty{true};
  mutable Mat4 mTransform;
};
} // namespace aw
