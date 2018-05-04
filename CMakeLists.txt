cmake_minimum_required(VERSION 3.6)

project(awRevolt VERSION 0.0.1 DESCRIPTION "awRevolt engine")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS "ON")

message(STATUS "SYSTEM NAME: ${CMAKE_SYSTEM_NAME}")

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

set(INC_DIR "include")
set(SRC_DIR "src")

set(INC_DIR_AW "${INC_DIR}/aw")
set(SRC_DIR_AW "${SRC_DIR}/aw")

set(HEADER_FILES
)

set(SOURCE_FILES
)

add_subdirectory(${INC_DIR_AW})
add_subdirectory(${SRC_DIR_AW})

set(AW_BUILD_TEST false CACHE BOOL "Builds test application instead of library")
set(CMAKE_BUILD_TYPE Debug CACHE STRING "Choose a build type")

if(AW_BUILD_TEST)
  if(AW_ANDROID)
    message(error "Test target is not supported for android builds")
  endif()

  set(TEST_FILES test/main.cpp)
  add_executable(${PROJECT_NAME} ${SOURCE_FILES} ${HEADER_FILES} ${TEST_FILES})
  target_link_libraries(${PROJECT_NAME} jsoncpp GL sfml-window-d sfml-system-d)
else()
  add_library(${PROJECT_NAME} SHARED ${SOURCE_FILES} ${HEADER_FILES})

  if(AW_DESKTOP)
    include (GNUInstallDirs)
    install(TARGETS ${PROJECT_NAME}
      LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
      PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
    install (
      DIRECTORY ${INC_DIR_AW}
      DESTINATION include
      FILES_MATCHING PATTERN "*.h*")
  else(AW_ANDROID)
    include_directories(${CMAKE_ANDROID_NDK}/sources/third_party/)
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
endif()

set_target_properties(${PROJECT_NAME} PROPERTIES SOVERSION 1)
target_include_directories(${PROJECT_NAME} PUBLIC ${INC_DIR} )
target_include_directories(${PROJECT_NAME} PRIVATE ${SRC_DIR} )
