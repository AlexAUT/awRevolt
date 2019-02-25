add_subdirectory(impl)

add_to_target(awUtils PRIVATE fileDialog.cpp)
add_to_target(awUtils PRIVATE fileInputStream.cpp)
add_to_target(awUtils PRIVATE fileOutputStream.cpp)
add_to_target(awUtils PRIVATE path.cpp)
