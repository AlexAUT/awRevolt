#pragma once

#include <aw/utils/math/matrix.hpp>
#include <aw/utils/math/quaternion.hpp>
#include <aw/utils/math/vector.hpp>

#include <functional>

namespace aw
{
class Transform
{
public:
  Transform() = default;
  explicit Transform(std::function<void()> listenerCallback);

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

  // This can be used to poll for changes, but you have to reset it yourself (first param)
  // Use this function to reset and get the old value of hasReset
  unsigned getVersionNumber() const;

private:
  void invalidTransformCache();

private:
  bool mOffOrigin{false};
  Vec3 mOrigin{0.f, 0.f, 0.f};
  Vec3 mPosition{0.f, 0.f, 0.f};
  Vec3 mScale{1.f, 1.f, 1.f};
  Quaternion mRotation{1.f, 0.f, 0.f, 0.f};

  unsigned mVersion{1};
  mutable unsigned mCachedTransformVersion{0};
  mutable Mat4 mTransform;

  std::function<void()> mChangeListener;
};
} // namespace aw
