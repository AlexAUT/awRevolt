#
add_subdirectory(math)

set(SOURCE_FILES ${SOURCE_FILES}
    ${CMAKE_CURRENT_SOURCE_DIR}/date.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/log.cpp
    PARENT_SCOPE)
