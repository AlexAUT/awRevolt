add_subdirectory(intersectors)

target_sources(awUtils
  PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}/AABB.hpp
  ${CMAKE_CURRENT_SOURCE_DIR}/octree.hpp
  ${CMAKE_CURRENT_SOURCE_DIR}/ray.hpp
  ${CMAKE_CURRENT_SOURCE_DIR}/intersectors.hpp
)
