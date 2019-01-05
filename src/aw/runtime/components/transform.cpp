#include <aw/runtime/components/transform.hpp>

#include <aw/utils/math/vector.hpp>

std::ostream& operator<<(std::ostream& stream, const aw::ecs::components::Transform& transform)
{
  stream << "Transform: {\n";
  stream << "\tPosition:\t" << transform.getPosition() << "\n";
  stream << "\tScale:\t\t" << transform.getScale() << "\n";
  stream << "\tRotation:\t" << transform.getRotiation() << "\n";
  stream << "\tLocal transform:\t" << transform.getLocalTransform() << "\n";
  stream << "\tGlobal transform:\t" << transform.getGlobalTransform() << "\n";
  stream << "}";

  return stream;
}
