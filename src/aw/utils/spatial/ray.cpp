#include <aw/utils/spatial/ray.hpp>

std::ostream& operator<<(std::ostream& stream, const aw::Ray& ray)
{
  stream << "Ray: {\n";
  stream << "\tOrigin: " << ray.origin << "\n";
  stream << "\tDir: \t " << ray.dir << "\n}";

  return stream;
}
