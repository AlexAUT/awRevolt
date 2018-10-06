#SFML
set(SFML_BUILD_AUDIO OFF)
set(SFML_BUILD_NETWORK OFF)
add_subdirectory(dependencies/sfml)

#Assimp
set(ASSIMP_BUILD_ALL_IMPORTERS_BY_DEFAULT OFF CACHE BOOL "a")
set(ASSIMP_BUILD_TESTS OFF CACHE BOOL "a")
set(ASSIMP_BUILD_SAMPLES OFF CACHE BOOL "a")
set(ASSIMP_BUILD_ASSIMP_TOOLS OFF CACHE BOOL "a")
set(ASSIMP_BUILD_FBX_IMPORTER ON CACHE BOOL "a")
set(ASSIMP_BUILD_OBJ_IMPORTER ON CACHE BOOL "a")
set(ASSIMP_BUILD_COLLADA_IMPORTER ON CACHE BOOL "a")
add_subdirectory(dependencies/assimp)

set(awGraphicsDependencies awUtils sfml-graphics sfml-window sfml-system assimp)

