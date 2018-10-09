add_subdirectory(math)
add_subdirectory(spatial)

set(HEADER_FILES_UTILS ${HEADER_FILES_UTILS}
    ${CMAKE_CURRENT_SOURCE_DIR}/clock.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/color.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/colors.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/date.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/assetInputStream.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/log.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/path.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/rect.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/streamReading.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/time.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/types.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/typeChecks.hpp
    PARENT_SCOPE)
