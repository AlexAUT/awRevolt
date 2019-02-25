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
option(AW_BUILD_UITLS "Build the utils module" ON)
option(AW_BUILD_GRAPHICS "Build the graphics module" ON)
option(AW_BUILD_RUNTIME "Build the runtime module" ON)
option(AW_BUILD_ENGINE "Build the engine module" ON)
option(AW_BUILD_GUI "Build the gui module" ON)

#Create configure file
configure_file(cmake/config.hpp.in include/aw/config.hpp)

if(AW_BUILD_DEPENDENCIES)
  include (ExternalProject)

  set(CMAKE_FLAGS
    -DBUILD_SHARED_LIBS=${BUILD_SHARED_LIBS}
    -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    -DCMAKE_INSTALL_PREFIX=${CMAKE_INSTALL_PREFIX}
  )
  message(STATUS "CMAKE FLAGS: ${CMAKE_FLAGS}")

  # Build dependencies
  if(AW_BUILD_UITLS)
    include(cmake/buildDependencies/awUtils.cmake)
  endif()
  if(AW_BUILD_GRAPHICS)
    include(cmake/buildDependencies/awGraphics.cmake)
  endif()
  if(AW_BUILD_RUNTIME)
    include(cmake/buildDependencies/awRuntime.cmake)
  endif()
  if(AW_BUILD_ENGINE)
    include(cmake/buildDependencies/awEngine.cmake)
  endif()
  if(AW_BUILD_GUI)
    include(cmake/buildDependencies/awGUI.cmake)
  endif()


  ExternalProject_Add (awRevoltBuild
    DEPENDS ${AW_DEPENDENCIES}
    SOURCE_DIR ${PROJECT_SOURCE_DIR}
    CMAKE_ARGS -DAW_BUILD_DEPENDENCIES=OFF ${CMAKE_FLAGS} 
    BINARY_DIR ${CMAKE_CURRENT_BINARY_DIR}/build
  )

  return()
endif()

# Show warnings for engine code
include(cmake/enableWarnings.cmake)

#Define awRevolt targets, source files will be added in the sub directories include/src
if(AW_BUILD_UITLS)
  add_library(awUtils)
  include(cmake/setDependencies/awUtils.cmake)
endif()
if(AW_BUILD_GRAPHICS)
  add_library(awGraphics)
  include(cmake/setDependencies/awGraphics.cmake)
endif()
if(AW_BUILD_RUNTIME)
  add_library(awRuntime)
  include(cmake/setDependencies/awRuntime.cmake)
endif()
if(AW_BUILD_ENGINE)
  add_library(awEngine)
  include(cmake/setDependencies/awEngine.cmake)
endif()
if(AW_BUILD_GUI)
  add_library(awGUI)
  include(cmake/setDependencies/awGUI.cmake)
endif()

#Add include to public include dir
target_include_directories(awUtils PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>  
  $<INSTALL_INTERFACE:include/>
)

set(AW_INCLUDE_DIR 
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>  
  $<INSTALL_INTERFACE:include>  # <prefix>/include/mylib PUBLIC
)
target_include_directories(awUtils PUBLIC ${AW_INCLUDE_DIR})
target_include_directories(awGraphics PUBLIC ${AW_INCLUDE_DIR})
target_include_directories(awRuntime PUBLIC ${AW_INCLUDE_DIR})
target_include_directories(awEngine PUBLIC ${AW_INCLUDE_DIR})
target_include_directories(awGUI PUBLIC ${AW_INCLUDE_DIR})
target_include_directories(awUtils PRIVATE ${CMAKE_CURRENT_BINARY_DIR}/include)
target_include_directories(awGraphics PRIVATE ${CMAKE_CURRENT_BINARY_DIR}/include)
target_include_directories(awRuntime PRIVATE ${CMAKE_CURRENT_BINARY_DIR}/include)
target_include_directories(awEngine PRIVATE ${CMAKE_CURRENT_BINARY_DIR}/include)
target_include_directories(awGUI PRIVATE ${CMAKE_CURRENT_BINARY_DIR}/include)

include(cmake/addFilesToTarget.cmake)
# Adds sources/includes to targets
add_subdirectory(include/aw)
add_subdirectory(src/aw)

# Export targets
include(GNUInstallDirs)
if(AW_BUILD_UITLS)
  include(cmake/export/awUtils.cmake)
endif()
if(AW_BUILD_GRAPHICS)
  include(cmake/export/awGraphics.cmake)
endif()
if(AW_BUILD_RUNTIME)
  include(cmake/export/awRuntime.cmake)
endif()
if(AW_BUILD_ENGINE)
  include(cmake/export/awEngine.cmake)
endif()
if(AW_BUILD_GUI)
  include(cmake/export/awGUI.cmake)
endif()

