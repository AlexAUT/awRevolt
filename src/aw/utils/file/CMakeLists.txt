add_subdirectory(impl)

target_sources(awUtils
  PRIVATE
  ${CMAKE_CURRENT_SOURCE_DIR}/fileDialog.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/fileInputStream.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/fileOutputStream.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/path.cpp
)
