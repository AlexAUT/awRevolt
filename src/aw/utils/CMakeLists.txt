#
add_subdirectory(math)
add_subdirectory(impl)
set(SOURCE_FILES ${SOURCE_FILES}
    ${CMAKE_CURRENT_SOURCE_DIR}/clock.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/date.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/assetInputStream.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/log.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/path.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/streamReading.cpp
    PARENT_SCOPE)

