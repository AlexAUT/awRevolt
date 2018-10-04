add_subdirectory(runtime)

set(SOURCE_FILES_ENGINE ${SOURCE_FILES_ENGINE}
    ${CMAKE_CURRENT_SOURCE_DIR}/engine.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/settings.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/window.cpp
    PARENT_SCOPE)
