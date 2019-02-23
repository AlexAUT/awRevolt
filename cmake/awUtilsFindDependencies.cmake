message(STATUS "SEARCH: ${CMAKE_PREFIX_PATH}")
set(CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH} ${DEPS_INSTALL_DIR}/share)
message(STATUS "SEARCH: ${CMAKE_PREFIX_PATH}")
#tinyfd
find_package(tinyfd REQUIRED)
target_link_libraries(awUtils tinyfd::tinyfd)
