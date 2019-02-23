add_subdirectory(intersectors)

target_sources(awUtils
  PRIVATE
  ${CMAKE_CURRENT_SOURCE_DIR}/AABB.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/ray.cpp
)
