#
add_subdirectory(file)
add_subdirectory(math)
add_subdirectory(impl)
add_subdirectory(spatial)
add_subdirectory(time)
set(SOURCE_FILES_UTILS ${SOURCE_FILES_UTILS}
    ${CMAKE_CURRENT_SOURCE_DIR}/log.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/streamReading.cpp
    PARENT_SCOPE)

