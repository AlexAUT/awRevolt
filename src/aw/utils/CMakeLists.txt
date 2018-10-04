#
add_subdirectory(math)
add_subdirectory(impl)
add_subdirectory(spatial)
set(SOURCE_FILES_UTILS ${SOURCE_FILES_UTILS}
    ${CMAKE_CURRENT_SOURCE_DIR}/date.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/assetInputStream.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/log.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/path.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/streamReading.cpp
    PARENT_SCOPE)

