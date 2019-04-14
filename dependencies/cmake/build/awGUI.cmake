#nanovg
ExternalProject_Add(nanovg
  DOWNLOAD_DIR "${CMAKE_CURRENT_SOURCE_DIR}/dependencies/"
  SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/dependencies/nanovg"
  DOWNLOAD_COMMAND ""
  UPDATE_COMMAND ${CMAKE_COMMAND} -E copy
    ${CMAKE_CURRENT_SOURCE_DIR}/cmake/dependencies/nanovg.cmake
    ${CMAKE_CURRENT_SOURCE_DIR}/dependencies/nanovg/CMakeLists.txt
  CMAKE_ARGS ${CMAKE_FLAGS}
)
set(AW_DEPENDENCIES ${AW_DEPENDENCIES} nanovg)
