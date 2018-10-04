if(AW_ANDROID)
  set(SOURCE_FILES_UTILS ${SOURCE_FILES_UTILS}
    ${CMAKE_CURRENT_SOURCE_DIR}/androidAssetBuffer.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/androidStreamBuffer.cpp
    PARENT_SCOPE)
  set(HEADER_FILES_UTILS ${HEADER_FILES_UTILS}
    ${CMAKE_CURRENT_SOURCE_DIR}/androidAssetBuffer.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/androidStreamBuffer.hpp
    PARENT_SCOPE)
endif()
