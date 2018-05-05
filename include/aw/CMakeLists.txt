#
add_subdirectory(engine)
add_subdirectory(graphics)
add_subdirectory(module)
add_subdirectory(opengl)
add_subdirectory(reflection)
add_subdirectory(utils)

set(SOURCE_FILES ${SOURCE_FILES} PARENT_SCOPE)
set(HEADER_FILES ${HEADER_FILES} PARENT_SCOPE)
