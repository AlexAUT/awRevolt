if(AW_ANDROID)
  add_to_target(awUtils PRIVATE androidAssetBuffer.cpp)
  add_to_target(awUtils PRIVATE androidStreamBuffer.cpp)
  add_to_target(awUtils PRIVATE androidAssetBuffer.hpp)
  add_to_target(awUtils PRIVATE androidStreamBuffer.hpp)
  target_sources(awUtils
    PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/androidAssetBuffer.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/androidStreamBuffer.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/androidAssetBuffer.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/androidStreamBuffer.hpp
  )
endif()
