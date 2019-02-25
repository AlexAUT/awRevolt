cmake_minimum_required(VERSION 3.6)

#native file dialog has no cmake script to create a target
include(GNUInstallDirs)

add_library(sqlite3)

target_sources(sqlite3
  PRIVATE
  ${CMAKE_CURRENT_SOURCE_DIR}/sqlite3.c
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/sqlite3.h>  
  $<INSTALL_INTERFACE:include/sqlite3.h>  # <prefix>/include/mylib PUBLIC
)

target_include_directories(sqlite3
  PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>  
  $<INSTALL_INTERFACE:include>  # <prefix>/include/mylib PUBLIC
)


install(TARGETS
        sqlite3
        EXPORT sqlite3Config
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
export(TARGETS
       sqlite3
       NAMESPACE sqlite3::
       FILE "${CMAKE_CURRENT_BINARY_DIR}/sqlite3Config.cmake"
)
install(EXPORT
        sqlite3Config
        DESTINATION "${CMAKE_INSTALL_DATADIR}/sqlite3/cmake"
        NAMESPACE sqlite3::
)

install(FILES sqlite3.h DESTINATION include/sqlite3)

