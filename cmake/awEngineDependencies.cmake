
#jsoncpp
if(AW_ANDROID)
  set(jsoncpp_DIR "${THIRD_PARTY_DIR}/lib/${ANDROID_ABI}/cmake/jsoncpp")
else(AW_ANDROID)
  set(jsoncpp_DIR "${THIRD_PARTY_DIR}/lib64/cmake/jsoncpp")
endif()
find_package(jsoncpp REQUIRED)

#target_include_directories(awEngine PUBLIC dependencies/jsoncpp/include)
set(awEngineDependencies jsoncpp_lib awGraphics awUtils)
