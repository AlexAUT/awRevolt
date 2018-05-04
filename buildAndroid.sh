set -e

mkdir -p buildAndroid
cd buildAndroid
cmake -DCMAKE_SYSTEM_NAME=Android -DCMAKE_ANDROID_NDK=/home/alex/Android/Sdk/ndk-bundle/ -DCMAKE_ANDROID_NDK_TOOLCHAIN_VERSION=clang -DCMAKE_ANDROID_STL_TYPE=c++_shared -DCMAKE_ANDROID_ARCH_ABI=armeabi-v7a -DCMAKE_BUILD_TYPE=Release -DBUILD_SHARED_LIBS=true ..
make -j 8
make install
cd ..
