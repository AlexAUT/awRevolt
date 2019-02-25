add_to_target(awGraphics PUBLIC commonTypes.hpp)
add_to_target(awGraphics PUBLIC opengl.hpp)
add_to_target(awGraphics PUBLIC openglExt.hpp)

if(AW_USE_OPENGL)
  add_to_target(awGraphics PUBLIC /impl/gl.hpp)
endif()
