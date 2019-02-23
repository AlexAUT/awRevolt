ExternalProject_Add(tinyfd
  DOWNLOAD_DIR "${CMAKE_CURRENT_SOURCE_DIR}/dependencies/"
  SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/dependencies/tinyfd"
  DOWNLOAD_COMMAND ""
  UPDATE_COMMAND ${CMAKE_COMMAND} -E copy
    ${CMAKE_CURRENT_SOURCE_DIR}/cmake/dependencies/tinyFileDialogs.cmake
    ${CMAKE_CURRENT_SOURCE_DIR}/dependencies/tinyfd/CMakeLists.txt
    CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${DEPS_INSTALL_DIR}
  )


