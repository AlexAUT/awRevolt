if(AW_ANDROID)
  set(SOURCE_FILES ${SOURCE_FILES}
    ${CMAKE_CURRENT_SOURCE_DIR}/androidAssetBuffer.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/androidStreamBuffer.cpp
    PARENT_SCOPE)
  set(HEADER_FILES ${HEADER_FILES}
    ${CMAKE_CURRENT_SOURCE_DIR}/androidAssetBuffer.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/androidStreamBuffer.hpp
    PARENT_SCOPE)
endif()
