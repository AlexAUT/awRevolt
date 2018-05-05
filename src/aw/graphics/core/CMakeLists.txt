#
set(SOURCE_FILES ${SOURCE_FILES}
    ${CMAKE_CURRENT_SOURCE_DIR}/bufferObject.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/camera.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/image.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/indicesBuffer.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/shaderProgram.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/shaderStage.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/texture2D.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/vertexBuffer.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/vertexArrayObject.cpp
    PARENT_SCOPE)

  set(HEADER_FILES ${HEADER_FILES}
    ${CMAKE_CURRENT_SOURCE_DIR}/stb_image.hpp
    PARENT_SCOPE)
