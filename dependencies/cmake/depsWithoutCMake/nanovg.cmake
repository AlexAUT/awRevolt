cmake_minimum_required(VERSION 3.6)

#nanovg has no cmake script to create a target
include(GNUInstallDirs)

add_library(nanovg)
target_compile_definitions(nanovg PUBLIC NANOVG_GL3_IMPLEMENTATION)

target_sources(nanovg
  PRIVATE
  ${CMAKE_CURRENT_SOURCE_DIR}/src/nanovg.c

  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src/nanovg.h>  
  $<INSTALL_INTERFACE:/nanovg.h>
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src/nanovg_gl.h>  
  $<INSTALL_INTERFACE:/nanovg_gl.h>
)

target_include_directories(nanovg
  PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>  
  $<INSTALL_INTERFACE:include/>
)


install(TARGETS
        nanovg
        EXPORT nanovgConfig
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
export(TARGETS
       nanovg
       NAMESPACE nanovg::
       FILE "${CMAKE_CURRENT_BINARY_DIR}/nanovgConfig.cmake"
)
install(EXPORT
        nanovgConfig
        DESTINATION "${CMAKE_INSTALL_DATADIR}/nanovg/cmake"
        NAMESPACE nanovg::
)

install(FILES 
          ${CMAKE_CURRENT_SOURCE_DIR}/src/nanovg.h
          ${CMAKE_CURRENT_SOURCE_DIR}/src/nanovg_gl.h
        DESTINATION include/nanovg)

