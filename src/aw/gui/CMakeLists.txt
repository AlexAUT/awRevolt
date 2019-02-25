add_subdirectory(renderer)
add_subdirectory(style)
add_subdirectory(widgets)

add_to_target(awGUI PRIVATE gui.cpp)
