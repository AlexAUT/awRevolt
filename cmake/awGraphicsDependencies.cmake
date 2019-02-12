#SFML
if(AW_ANDROID)
  set(SFML_DIR "${THIRD_PARTY_DIR}/sfml/lib/${ANDROID_ABI}/cmake/SFML")
else(AW_ANDROID)
  set(SFML_DIR "${THIRD_PARTY_DIR}//lib/cmake/SFML")
endif(AW_ANDROID)

find_package(SFML 2 COMPONENTS window system REQUIRED)

#Assimp
set(assimp_DIR "${THIRD_PARTY_DIR}/lib/${ANDROID_ABI}/cmake/assimp-4.1")
find_package(assimp REQUIRED)

add_subdirectory(dependencies/etc2comp)
target_include_directories(awGraphics PUBLIC dependencies/etc2comp/EtcLib/Etc)
target_include_directories(awGraphics PUBLIC dependencies/etc2comp/EtcLib/EtcCodec)

set(awGraphicsDependencies awUtils sfml-window sfml-system assimp::assimp EtcLib)

