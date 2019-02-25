add_subdirectory(intersectors)

add_to_target(awUtils PUBLIC AABB.hpp)
add_to_target(awUtils PUBLIC octree.hpp)
add_to_target(awUtils PUBLIC ray.hpp)
add_to_target(awUtils PUBLIC intersectors.hpp)
