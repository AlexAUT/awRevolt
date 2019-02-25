target_link_libraries(awGUI PRIVATE awUtils)

#nanovg
set(nanovg_DIR ${CMAKE_INSTALL_PREFIX}/share/nanovg/cmake/)
find_package(nanovg REQUIRED)
target_link_libraries(awGUI PRIVATE nanovg::nanovg)

