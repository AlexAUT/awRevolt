target_link_libraries(awGraphics PRIVATE awUtils)

#glm
set(glm_DIR ${CMAKE_INSTALL_PREFIX}/lib64/cmake/glm/)
find_package(glm REQUIRED)
target_link_libraries(awGraphics PUBLIC glm)

#sfml
set(SFML_DIR ${CMAKE_INSTALL_PREFIX}/lib/cmake/SFML)
message(STATUS "SFML DIr: ${SFML_DIR}")
find_package(SFML 2 COMPONENTS window system REQUIRED)
target_link_libraries(awGraphics PRIVATE sfml-system)

