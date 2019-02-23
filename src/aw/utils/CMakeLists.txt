add_subdirectory(file)
add_subdirectory(math)
add_subdirectory(spatial)
add_subdirectory(time)

target_sources(awUtils
  PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/color.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/log.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/streamReading.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/stringFormat.cpp
)

