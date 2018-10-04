cmake_minimum_required(VERSION 3.6)

project(awRevolt VERSION 0.0.1 DESCRIPTION "awRevolt engine")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS "ON")

if(${CMAKE_SYSTEM_NAME} MATCHES "Emscripten")
  set(AW_EMSCRIPTEN true)
  set(AW_USE_GLES true)
  add_definitions(-DAW_USE_GLES)
  add_definitions(-DAW_EMSCRIPTEN)
elseif(${CMAKE_SYSTEM_NAME} MATCHES "Android")
  set(AW_ANDROID true)
  set(AW_USE_GLES true)
  add_definitions(-DAW_USE_GLES)
  add_definitions(-DAW_ANDROID)
else()
  set(AW_DESKTOP true)
  set(AW_USE_OPENGL true)
  add_definitions(-DAW_DESKTOP)
  add_definitions(-DAW_USE_OPENGL)
endif()

add_definitions(-DGLM_FORCE_SILENT_WARNINGS)

if(MSVC)
# Force to always compile with W4
  if(CMAKE_CXX_FLAGS MATCHES "/W[0-4]")
    string(REGEX REPLACE "/W[0-4]" "/W4" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
  else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
  endif()
elseif(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)
  # Update if necessary
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wno-long-long -pedantic")
endif()

#VARIABLES TO ENABLE/DISABLE MODULES
set(AW_BUILD_UTILS ON CACHE BOOL "Builds the utils module")
set(AW_BUILD_GRAPHICS ON CACHE BOOL "Builds the graphics module")
set(AW_BUILD_ENGINE ON CACHE BOOL "Builds the engine module")
set(AW_BUILD_REFLECTION ON CACHE BOOL "Builds the reflection module")

set(GLM_INCLUDE_PATH "" CACHE PATH "Provide GLM path if not in default search path")
include_directories(${GLM_INCLUDE_PATH})

set(INC_DIR "include")
set(SRC_DIR "src")

set(INC_DIR_AW "${INC_DIR}/aw")
set(SRC_DIR_AW "${SRC_DIR}/aw")

set(HEADER_FILES_UTILS)
set(HEADER_FILES_GRAPHICS)
set(HEADER_FILES_ENGINE)
set(HEADER_FILES_REFLECTION)

set(SOURCE_FILES_UTILS)
set(SOURCE_FILES_GRAPHICS)
set(SOURCE_FILES_ENGINE)
set(SOURCE_FILES_REFLECTION)

add_subdirectory(${INC_DIR_AW})
add_subdirectory(${SRC_DIR_AW})

set(AW_BUILD_TEST false CACHE BOOL "Builds test application instead of library")
set(CMAKE_BUILD_TYPE Debug CACHE STRING "Choose a build type")

#GENERATE LIST WITH ENABLED TARGET NAMES
if(AW_BUILD_UTILS)
  set(AW_ENABLED_TARGETS "${AW_ENABLED_TARGETS}awUtils ")
  add_library(awUtils SHARED ${SOURCE_FILES_UTILS} ${HEADER_FILES_UTILS})
  set_target_properties(awUtils PROPERTIES SOVERSION 1)
endif()
if(AW_BUILD_GRAPHICS)
  set(AW_ENABLED_TARGETS "${AW_ENABLED_TARGETS}awGraphics ")
  add_library(awGraphics SHARED ${SOURCE_FILES_GRAPHICS} ${HEADER_FILES_GRAPHICS})
  set_target_properties(awGraphics PROPERTIES SOVERSION 1)
endif()
if(AW_BUILD_ENGINE)
  set(AW_ENABLED_TARGETS "${AW_ENABLED_TARGETS}awEngine ")
  add_library(awEngine SHARED ${SOURCE_FILES_ENGINE} ${HEADER_FILES_ENGINE})
  set_target_properties(awEngine PROPERTIES SOVERSION 1)
endif()
if(AW_BUILD_REFLECTION)
  set(AW_ENABLED_TARGETS "${AW_ENABLED_TARGETS}awReflection ")
  add_library(awReflection SHARED ${SOURCE_FILES_REFLECTION} ${HEADER_FILES_REFLECTION})
  set_target_properties(awReflection PROPERTIES SOVERSION 1)
endif()

if(AW_DESKTOP)
  if(AW_BUILD_ENGINE)
    target_link_libraries(awEngine awGraphics awUtils)
    # Find SFML
    set(SFML_DIR "${CMAKE_SOURCE_DIR}/extlibs/lib/cmake/SFML")
    find_package(SFML 2 REQUIRED  window system)
    target_link_libraries(awEngine sfml-window sfml-system)

    if(WIN32)
      target_link_libraries(awEngine jsoncpp assimp)
    else()
      # Setup assimp, we need to create a target ourself
      FILE(GLOB ASSIMP_DIR "${CMAKE_SOURCE_DIR}/extlibs/lib/cmake/assimp*")
      find_package(ASSIMP REQUIRED)
      if (ASSIMP_FOUND)
        set(ASSIMP_LIBRARY "assimp")
        add_library(${ASSIMP_LIBRARY} SHARED IMPORTED)
        set_target_properties(${ASSIMP_LIBRARY} PROPERTIES
          IMPORTED_LOCATION "${ASSIMP_LIBRARY_DIRS}/libassimp.so")
      endif()
      target_link_libraries(awEngine ${ASSIMP_LIBRARY})
      #jsoncpp
      set(jsoncpp_DIR "${CMAKE_SOURCE_DIR}/extlibs/lib64/cmake/jsoncpp")
      find_package(jsoncpp REQUIRED)
      target_link_libraries(awEngine jsoncpp)
    endif()
  endif(AW_BUILD_ENGINE)
  if(AW_BUILD_GRAPHICS)
    target_link_libraries(awGraphics awUtils) 
    if(WIN32)
      target_link_libraries(awGraphics opengl32)
    else()
      target_link_libraries(awGraphics GL)
    endif()
  endif(AW_BUILD_GRAPHICS)
  if(AW_BUILD_REFLECTION)
    target_link_libraries(awUtils)
  endif()

  if(WIN32)
  else()
    # Install library
    include (GNUInstallDirs)
    install(TARGETS awUtils
      LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
      PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
    install (
      DIRECTORY ${INC_DIR_AW}
      DESTINATION include
      FILES_MATCHING PATTERN "*.h*")
    install (
      DIRECTORY ${INC_DIR_AW}
      DESTINATION include
      FILES_MATCHING PATTERN "*.inl")
  endif()
else(AW_ANDROID)
  include_directories(${CMAKE_ANDROID_NDK}/sources/third_party/)
  include_directories(${CMAKE_ANDROID_NDK}/sources/third_party/include)
  include_directories(${CMAKE_ANDROID_NDK}/sources/third_party/sfml/include)
  include_directories(${CMAKE_ANDROID_NDK}/sources/third_party/jsoncpp/include)
  set(INSTALL_DIR ${CMAKE_ANDROID_NDK}/sources/third_party/awRevolt/)
  message(STATUS "Android: ${INSTALL_DIR}")
  install(TARGETS ${PROJECT_NAME}
    LIBRARY DESTINATION ${INSTALL_DIR}/lib/${CMAKE_ANDROID_ARCH_ABI}
    PUBLIC_HEADER DESTINATION ${INSTALL_DIR}/include/
  )
  install (
    DIRECTORY ${INC_DIR_AW}
    DESTINATION ${INSTALL_DIR}/include/
    FILES_MATCHING PATTERN "*.h*" 
  )
endif()

#We only set this once, since every other target depends on awUtils
target_include_directories(awUtils PUBLIC ${INC_DIR})
target_include_directories(awUtils PUBLIC ${SRC_DIR})

if(AW_DESKTOP)
  if (EXISTS "${CMAKE_SOURCE_DIR}/flightGame/CMakeLists.txt")
    message(STATUS "Flight game found")
      add_subdirectory(flightGame)
  endif()
endif()
