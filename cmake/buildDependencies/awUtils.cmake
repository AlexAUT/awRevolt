#tinyfd
ExternalProject_Add(tinyfd
  DOWNLOAD_DIR "${CMAKE_CURRENT_SOURCE_DIR}/dependencies/"
  SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/dependencies/tinyfd"
  DOWNLOAD_COMMAND ""
  UPDATE_COMMAND ${CMAKE_COMMAND} -E copy
    ${CMAKE_CURRENT_SOURCE_DIR}/cmake/dependencies/tinyFileDialogs.cmake
    ${CMAKE_CURRENT_SOURCE_DIR}/dependencies/tinyfd/CMakeLists.txt
    CMAKE_ARGS ${CMAKE_FLAGS}
)
set(AW_DEPENDENCIES ${AW_DEPENDENCIES} tinyfd)

#glm
ExternalProject_Add(glm
  DOWNLOAD_DIR "${CMAKE_CURRENT_SOURCE_DIR}/dependencies/"
  SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/dependencies/glm"
  DOWNLOAD_COMMAND ""
  CMAKE_ARGS ${CMAKE_FLAGS} -DGLM_TEST_ENABLE=OFF
)
set(AW_DEPENDENCIES ${AW_DEPENDENCIES} glm)

#sfml
ExternalProject_Add(sfml
  DOWNLOAD_DIR "${CMAKE_CURRENT_SOURCE_DIR}/dependencies/"
  SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/dependencies/sfml"
  DOWNLOAD_COMMAND ""
  CMAKE_ARGS ${CMAKE_FLAGS}
)
set(AW_DEPENDENCIES ${AW_DEPENDENCIES} sfml)
