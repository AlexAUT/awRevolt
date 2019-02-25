#tinyfd
set(tinyfd_DIR ${CMAKE_INSTALL_PREFIX}/share/tinyfd/cmake/)
message(STATUS "Tiny: ${tinyfd_DIR}")
find_package(tinyfd REQUIRED)
target_link_libraries(awUtils PRIVATE tinyfd::tinyfd)

#glm
set(glm_DIR ${CMAKE_INSTALL_PREFIX}/lib64/cmake/glm/)
find_package(glm REQUIRED)
target_link_libraries(awUtils PUBLIC glm)

#sfml
set(SFML_DIR ${CMAKE_INSTALL_PREFIX}/lib/cmake/SFML)
message(STATUS "SFML DIr: ${SFML_DIR}")
find_package(SFML 2 COMPONENTS network system REQUIRED)
target_link_libraries(awUtils PUBLIC sfml-network sfml-system)

