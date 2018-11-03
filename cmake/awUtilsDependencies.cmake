target_include_directories(awUtils PUBLIC dependencies/glm)
target_compile_definitions(awUtils PUBLIC GLM_FORCE_SILENT_WARNINGS)

#native file dialog has no cmake script to create a target
set(TINYFD_SOURCES "dependencies/tinyfd/tinyfiledialogs.c")
add_library(tinyfd STATIC ${TINYFD_SOURCES})
set_target_properties(tinyfd PROPERTIES SOVERSION 1)
target_include_directories(tinyfd PUBLIC "dependencies/tinyfd")

#SFML network (logging)
if(AW_ANDROID)
  set(SFML_DIR "${THIRD_PARTY_DIR}/sfml/lib/${ANDROID_ABI}/cmake/SFML")
else(AW_ANDROID)
  set(SFML_DIR "${THIRD_PARTY_DIR}//lib/cmake/SFML")
endif(AW_ANDROID)

find_package(SFML 2 COMPONENTS network system REQUIRED)

set(awUtilsDependencies sfml-network sfml-system tinyfd)

