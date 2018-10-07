#since nanovg doesnt use cmake we need to define the target ourself
set(NANOVG_SOURCES "dependencies/nanovg/src/nanovg.c")
add_library(nanovg SHARED ${NANOVG_SOURCES})
set_target_properties(nanovg PROPERTIES SOVERSION 1)
target_include_directories(nanovg PUBLIC "dependencies/nanovg/src/")
target_compile_definitions(nanovg PUBLIC NANOVG_GL3_IMPLEMENTATION)

set(awGUIDependencies awEngine awGraphics awUtils nanovg)
