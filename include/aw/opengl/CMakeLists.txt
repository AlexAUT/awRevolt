#OPENGL only when AW_USE_OPENGL is defined
if(AW_USE_OPENGL)
  set(IMPL_HEADER_FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/impl/gl_core_3_3.hpp
    )
endif()

set(HEADER_FILES ${HEADER_FILES}
    ${CMAKE_CURRENT_SOURCE_DIR}/loader.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/commonTypes.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/opengl.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/openglExt.hpp
    ${IMPL_HEADER_FILES}
    PARENT_SCOPE)
