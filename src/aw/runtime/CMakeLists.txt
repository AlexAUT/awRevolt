#
add_subdirectory(components)
add_subdirectory(entitySystem)
add_subdirectory(loaders)
add_subdirectory(resourceManager)
add_subdirectory(scene)
add_subdirectory(systems)

set(SOURCE_FILES_ENGINE ${SOURCE_FILES_ENGINE} PARENT_SCOPE)
set(HEADER_FILES_ENGINE ${HEADER_FILES_ENGINE} PARENT_SCOPE)

