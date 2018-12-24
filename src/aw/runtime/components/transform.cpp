#include <aw/runtime/components/transform.hpp>

#include <aw/utils/math/vector.hpp>

namespace aw::ecs::components
{
Mat4 Transform::getTransform() const
{
  Mat4 scaling = glm::scale(Mat4(1.f), mScale);
  Mat4 rotation = glm::mat4_cast(mRotation);
  Mat4 translation = glm::translate(Mat4(1.f), mPosition);
  return translation * rotation * scaling;
}
} // namespace aw::ecs::components

std::ostream& operator<<(std::ostream& stream, const aw::ecs::components::Transform& transform)
{
  stream << "Transform: {\n";
  stream << "\tPosition:\t" << transform.getPosition() << "\n";
  stream << "\tScale:\t\t" << transform.getScale() << "\n";
  stream << "\tRotation:\t" << transform.getRotiation() << "\n";
  stream << "\tTransform:\t" << transform.getTransform() << "\n";
  stream << "}";

  return stream;
}
