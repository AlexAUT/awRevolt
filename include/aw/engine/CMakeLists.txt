add_subdirectory(runtime)

set(HEADER_FILES_ENGINE ${HEADER_FILES_ENGINE}
    ${CMAKE_CURRENT_SOURCE_DIR}/engine.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/logCategories.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/settings.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/window.hpp
    PARENT_SCOPE)
