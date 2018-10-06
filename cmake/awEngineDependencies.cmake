set(JSONCPP_WITH_TESTS OFF CACHE BOOL "a")
set(JSONCPP_WITH_POST_BUILD_UNITTEST OFF CACHE BOOL "a")
add_subdirectory(dependencies/jsoncpp)

target_include_directories(awEngine PUBLIC dependencies/jsoncpp/include)
set(awEngineDependencies jsoncpp_lib awGraphics awUtils)
