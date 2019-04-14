ExternalProject_Add(sqlite3
  DOWNLOAD_DIR "${CMAKE_CURRENT_SOURCE_DIR}/dependencies/"
  SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/dependencies/sqlite3"
  URL "https://www.sqlite.org/2019/sqlite-amalgamation-3270100.zip"
  UPDATE_COMMAND ${CMAKE_COMMAND} -E copy
    ${CMAKE_CURRENT_SOURCE_DIR}/cmake/dependencies/sqlite3.cmake
    ${CMAKE_CURRENT_SOURCE_DIR}/dependencies/sqlite3/CMakeLists.txt
    CMAKE_ARGS ${CMAKE_FLAGS}
)
set(AW_DEPENDENCIES ${AW_DEPENDENCIES} sqlite3)
