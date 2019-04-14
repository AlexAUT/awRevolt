cmake_minimum_required(VERSION 3.6)

#native file dialog has no cmake script to create a target
include(GNUInstallDirs)

add_library(tinyfd)

target_sources(tinyfd
  PRIVATE
  ${CMAKE_CURRENT_SOURCE_DIR}/tinyfiledialogs.c
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/tinyfiledialogs.h>  
  $<INSTALL_INTERFACE:include/tinyfiledialogs.h>  # <prefix>/include/mylib PUBLIC
)

target_include_directories(tinyfd
  PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>  
  $<INSTALL_INTERFACE:include>  # <prefix>/include/mylib PUBLIC
)


install(TARGETS
        tinyfd
        EXPORT tinyfdConfig
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
export(TARGETS
       tinyfd
       NAMESPACE tinyfd::
       FILE "${CMAKE_CURRENT_BINARY_DIR}/tinyfdConfig.cmake"
)
install(EXPORT
        tinyfdConfig
        DESTINATION "${CMAKE_INSTALL_DATADIR}/tinyfd/cmake"
        NAMESPACE tinyfd::
)

install(FILES tinyfiledialogs.h DESTINATION include/tinyfd)

