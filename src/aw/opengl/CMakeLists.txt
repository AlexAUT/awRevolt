add_to_target(awRuntime PRIVATE opengl.cpp)

if(AW_USE_OPENGL)
  add_to_target(awRuntime PRIVATE /impl/gl.cpp)
endif()

