add_subdirectory(file)
add_subdirectory(math)
add_subdirectory(spatial)
add_subdirectory(time)

add_to_target(awUtils PRIVATE color.cpp)
add_to_target(awUtils PRIVATE log.cpp)
add_to_target(awUtils PRIVATE streamReading.cpp)
add_to_target(awUtils PRIVATE stringFormat.cpp)

