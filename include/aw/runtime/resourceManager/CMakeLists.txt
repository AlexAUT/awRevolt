add_subdirectory(factories)

set(HEADER_FILES_ENGINE ${HEADER_FILES_ENGINE}
  ${CMAKE_CURRENT_SOURCE_DIR}/resourceManager.hpp
  ${CMAKE_CURRENT_SOURCE_DIR}/resourceManager.inl
  ${CMAKE_CURRENT_SOURCE_DIR}/resourceRegistry.hpp
  ${CMAKE_CURRENT_SOURCE_DIR}/resourceRegistry.inl
  PARENT_SCOPE)

