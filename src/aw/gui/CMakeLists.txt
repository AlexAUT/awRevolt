add_subdirectory(renderer)
add_subdirectory(style)
add_subdirectory(widgets)

set(SOURCE_FILES_GUI ${SOURCE_FILES_GUI}
  ${CMAKE_CURRENT_SOURCE_DIR}/gui.cpp
  PARENT_SCOPE)
