cmake_minimum_required(VERSION 3.6)
include(cmake/enableWarnings.cmake)

option(AW_BUILD_DEPENDENCIES "Builds dependencies" ON)

#OS depending variables
if(${CMAKE_SYSTEM_NAME} MATCHES "Emscripten")
  set(AW_EMSCRIPTEN true)
  set(AW_USE_GLES true)
elseif(${CMAKE_SYSTEM_NAME} MATCHES "Android")
  set(AW_ANDROID true)
  set(AW_USE_GLES true)
  set(THIRD_PARTY_DIR "${CMAKE_ANDROID_NDK}/sources/third_party")
else()
  set(AW_DESKTOP true)
  set(AW_USE_OPENGL true)
  set(THIRD_PARTY_DIR "${CMAKE_CURRENT_SOURCE_DIR}/dependencies/precompiledDependencies")
endif()

#awRevolt uses features of c++17
set(CMAKE_CXX_STANDARD 17)


#VARIABLES TO ENABLE/DISABLE MODULES
#set(AW_BUILD_UTILS ON CACHE BOOL "Builds the utils module")
option(AW_BUILD_UITLS "Build the utils module" ON)


set(DEPS_INSTALL_DIR "${CMAKE_CURRENT_SOURCE_DIR}/dependencies/compiled")

if(AW_BUILD_DEPENDENCIES)
  include (ExternalProject)

  # Build dependencies
  if(AW_BUILD_UITLS)
    include(cmake/awUtilsBuildDependencies.cmake)
  endif()

  ExternalProject_Add (awRevoltBuild
  DEPENDS ${DEPENDENCIES}
  SOURCE_DIR ${PROJECT_SOURCE_DIR}
  CMAKE_ARGS -DAW_BUILD_DEPENDENCIES=OFF ${EXTRA_CMAKE_ARGS}
  INSTALL_COMMAND ""
  BINARY_DIR ${CMAKE_CURRENT_BINARY_DIR}/build)

  return()
endif()

#Define awRevolt targets, source files will be added in the sub directories include/src
add_library(awUtils)

#Add include to public include dir
target_include_directories(awUtils PUBLIC include)

# Adds sources/includes to targets
add_subdirectory(include/aw)
add_subdirectory(src/aw)

# Find dependencies
if(AW_BUILD_UITLS)
  include(cmake/awUtilsFindDependencies.cmake)
endif()


