add_subdirectory(renderer)
add_subdirectory(widgets)

set(HEADER_FILES_GUI ${HEADER_FILES_GUI}
  ${CMAKE_CURRENT_SOURCE_DIR}/gui.hpp
  PARENT_SCOPE)
