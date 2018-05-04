add_subdirectory(math)

set(HEADER_FILES ${HEADER_FILES}
    ${CMAKE_CURRENT_SOURCE_DIR}/date.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/log.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/path.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/types.hpp
    PARENT_SCOPE)
