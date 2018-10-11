target_include_directories(awUtils PUBLIC dependencies/glm)
target_compile_definitions(awUtils PUBLIC GLM_FORCE_SILENT_WARNINGS)

#native file dialog has no cmake script to create a target
set(TINYFD_SOURCES "dependencies/tinyfd/tinyfiledialogs.c")
add_library(tinyfd SHARED ${TINYFD_SOURCES})
set_target_properties(tinyfd PROPERTIES SOVERSION 1)
target_include_directories(tinyfd PUBLIC "dependencies/tinyfd")

set(awUtilsDependencies tinyfd)

