target_link_libraries(awEngine PRIVATE awRuntime awUtils)

#jsoncpp 
set(jsoncpp_DIR ${CMAKE_INSTALL_PREFIX}/lib64/cmake/jsoncpp/)
find_package(jsoncpp REQUIRED)
target_link_libraries(awRuntime PRIVATE jsoncpp)
