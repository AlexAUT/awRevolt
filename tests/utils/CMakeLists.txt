set(HEADER_FILES_TESTS ${HEADER_FILES_TESTS} PARENT_SCOPE)

set(SOURCE_FILES_TESTS ${SOURCE_FILES_TESTS}
  ${CMAKE_CURRENT_SOURCE_DIR}/testMessageBus.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/testStringFormat.cpp
  PARENT_SCOPE)

