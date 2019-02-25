target_link_libraries(awRuntime PRIVATE awGraphics)

#glm
set(glm_DIR ${CMAKE_INSTALL_PREFIX}/lib64/cmake/glm/)
find_package(glm REQUIRED)
target_link_libraries(awRuntime PRIVATE glm)

#assimp 
set(assimp_DIR ${CMAKE_INSTALL_PREFIX}/lib/cmake/assimp-4.1/)
find_package(assimp REQUIRED)
target_link_libraries(awRuntime PRIVATE assimp::assimp)
