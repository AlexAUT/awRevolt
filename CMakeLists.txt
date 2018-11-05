cmake_minimum_required(VERSION 3.6)
include(cmake/enableWarnings.cmake)

# OS DETECTION
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

#Android cmake is too old for 17, so android will pass it as CXX_FLAGS
if(NOT AW_ANDROID)
  set(CMAKE_CXX_STANDARD 17)
endif()

#VARIABLES TO ENABLE/DISABLE MODULES
#set(AW_BUILD_UTILS ON CACHE BOOL "Builds the utils module")
set(AW_BUILD_UTILS ON) #UTILS is mandatory
set(AW_BUILD_GRAPHICS ON CACHE BOOL "Builds the graphics module")
set(AW_BUILD_ENGINE ON CACHE BOOL "Builds the engine module")
set(AW_BUILD_REFLECTION ON CACHE BOOL "Builds the reflection module")
set(AW_BUILD_GUI ON CACHE BOOL "Builds the gui module")

set(AW_BUILD_ALL_TESTS ON CACHE BOOL "Builds tests for all modules")

set(INC_DIR "include")
set(SRC_DIR "src")
set(INC_DIR_AW "${INC_DIR}/aw")
set(SRC_DIR_AW "${SRC_DIR}/aw")

#These will be filled by the subdirectory cmake scripts
set(HEADER_FILES_UTILS)
set(HEADER_FILES_GRAPHICS)
set(HEADER_FILES_ENGINE)
set(HEADER_FILES_REFLECTION)
set(HEADER_FILES_GUI)
set(SOURCE_FILES_UTILS)
set(SOURCE_FILES_GRAPHICS)
set(SOURCE_FILES_ENGINE)
set(SOURCE_FILES_REFLECTION)
set(SOURCE_FILES_GUI)

add_subdirectory(${INC_DIR_AW})
add_subdirectory(${SRC_DIR_AW})

function(defineTarget targetName files targetList)
  #Add target to targetList
  set(${targetList} ${${targetList}} ${targetName} PARENT_SCOPE)

  add_library(${targetName} STATIC ${files})
  include(cmake/${targetName}Dependencies.cmake)
  target_link_libraries(${targetName} ${${targetName}Dependencies})
  set_target_properties(${targetName} PROPERTIES SOVERSION 1)
endfunction()

#GENERATE LIST WITH ENABLED TARGET NAMES
if(AW_BUILD_UTILS)
  defineTarget(awUtils "${SOURCE_FILES_UTILS};${HEADER_FILES_UTILS}" AW_ENABLED_TARGETS)
endif()

if(AW_BUILD_GRAPHICS)
  defineTarget(awGraphics "${SOURCE_FILES_GRAPHICS};${HEADER_FILES_GRAPHICS}" AW_ENABLED_TARGETS)
endif()
if(AW_BUILD_ENGINE)
  defineTarget(awEngine "${SOURCE_FILES_ENGINE};${HEADER_FILES_ENGINE}" AW_ENABLED_TARGETS)
endif()
if(AW_BUILD_REFLECTION)
  defineTarget(awReflection "${SOURCE_FILES_REFLECTION};${HEADER_FILES_REFLECTION}" AW_ENABLED_TARGETS)
endif()
if(AW_BUILD_GUI)
  defineTarget(awGUI "${SOURCE_FILES_GUI};${HEADER_FILES_GUI}" AW_ENABLED_TARGETS)
endif()

#We only set this once, since every other target depends on awUtils
#Since all awRevolt modules share the folder this will add all headers
target_include_directories(awUtils PUBLIC ${INC_DIR})
target_include_directories(awUtils PUBLIC ${SRC_DIR})



# Compile time defines
if(AW_USE_OPENGL AND AW_BUILD_GRAPHICS)
  target_compile_definitions(awGraphics PUBLIC AW_USE_OPENGL)
else(AW_USE_GLES AND AW_BUILD_GRAPHICS)
  target_compile_definitions(awGraphics PUBLIC AW_USE_GLES)
endif()
#OS detection, since everything depends on awUtils just set it there PUBLIC
if(AW_DESKTOP)
  target_compile_definitions(awUtils PUBLIC AW_DESKTOP)
elseif(AW_ANDROID)
  target_compile_definitions(awUtils PUBLIC AW_ANDROID)
elseif(AW_EMSCRIPTEN)
  target_compile_definitions(awUtils PUBLIC AW_EMSCRIPTEN)
endif()

# TEST FRAMEWORK
if(AW_BUILD_ALL_TESTS)
  set(TEST_DIR "tests")
  set(HEADER_FILES_TESTS)
  set(SOURCE_FILES_TESTS)
  add_subdirectory(${TEST_DIR})

  add_executable(awTests ${HEADER_FILES_TESTS} ${SOURCE_FILES_TESTS})
  target_link_libraries(awTests ${AW_ENABLED_TARGETS})
  message(STATUS "Deps: ${AW_ENABLED_TARGETS}")
  #Add external dependencies
  include(cmake/awTestsDependencies.cmake)
  target_link_libraries(awTests ${awTestsDependencies})
endif()
