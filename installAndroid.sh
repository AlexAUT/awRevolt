#Download dependencies
./downloadExtlibs.sh

: "${ANDROID_NDK:?Need to set ANDROID_NDK to the NDK root directory}"

ROOT_DIR=$(dirname "$0")

#install glm
cp -r extlibs/glm/glm $ANDROID_NDK/sources/third_party/include

# Build SFML
mkdir -p extlibs/sfml/buildAndroid
cd extlibs/sfml/buildAndroid
# Build sfml for all desktop types
mkdir debugShared
cd debugShared
cmake ../../ -DCMAKE_BUILD_TYPE=Debug -DBUILD_SHARED_LIBS=True \
             -DCMAKE_SYSTEM_NAME=Android -DCMAKE_ANDROID_NDK=$ANDROID_NDK \
             -DCMAKE_ANDROID_STL_TYPE=c++_shared -DCMAKE_ANDROID_NDK_TOOLCHAIN_VERSION=clang

make -j 8 && make install
cd ..
mkdir releaseShared
cd releaseShared
cmake ../../ -DCMAKE_BUILD_TYPE=Release -DBUILD_SHARED_LIBS=True \
             -DCMAKE_SYSTEM_NAME=Android -DCMAKE_ANDROID_NDK=$ANDROID_NDK \
             -DCMAKE_ANDROID_STL_TYPE=c++_shared -DCMAKE_ANDROID_NDK_TOOLCHAIN_VERSION=clang
make -j 8 && make install
cd ..
cd ../../../


# Build Assimp
mkdir -p extlibs/assimp/buildAndroid
cd extlibs/assimp/buildAndroid
cmake .. -DCMAKE_BUILD_TYPE=Release \
         -DCMAKE_INSTALL_PREFIX=$ANDROID_NDK/sources/third_party \
         -DCMAKE_SYSTEM_NAME=Android \
         -DCMAKE_ANDROID_NDK=$ANDROID_NDK \
         -DCMAKE_ANDROID_STL_TYPE=c++_shared -DCMAKE_ANDROID_NDK_TOOLCHAIN_VERSION=clang \
         -DASSIMP_BUILD_ALL_IMPORTERS_BY_DEFAULT=False \
         -DASSIMP_BUILD_TESTS=False \
         -DASSIMP_BUILD_SAMPLES=False \
         -DASSIMP_BUILD_OBJ_IMPORTER=True \
         -DASSIMP_BUILD_FBX_IMPORTER=True \
         -DASSIMP_BUILD_COLLADA_IMPORTER=True \
         -DASSIMP_BUILD_ASSIMP_TOOLS=False
make -j 8 && make install
cd ../../../

# JSONCPP
mkdir -p extlibs/jsoncpp/buildAndroid
cd extlibs/jsoncpp/buildAndroid
mkdir release
cd release
cmake ../.. -DCMAKE_BUILD_TYPE=Release \
         -DCMAKE_INSTALL_PREFIX=$ANDROID_NDK/sources/third_party \
         -DCMAKE_SYSTEM_NAME=Android \
         -DCMAKE_ANDROID_NDK=$ANDROID_NDK \
         -DCMAKE_ANDROID_STL_TYPE=c++_shared -DCMAKE_ANDROID_NDK_TOOLCHAIN_VERSION=clang \
         -DBUILD_SHARED_LIBS=True \
         -DBUILD_STATIC_LIBS=False \
         -DJSONCPP_WITHPOST_BUILD_UNITTEST=False \
         -DJSONCPP_WITH_TESTS=False
make -j 8 && make install

cd ..
mkdir -p debug
cd debug
cmake ../.. -DCMAKE_BUILD_TYPE=Debug \
         -DCMAKE_INSTALL_PREFIX=../../../ \
         -DDEBUG_LIBNAME_SUFFIX=-d \
         -DCMAKE_SYSTEM_NAME=Android \
         -DCMAKE_ANDROID_NDK=$ANDROID_NDK \
         -DCMAKE_ANDROID_STL_TYPE=c++_shared -DCMAKE_ANDROID_NDK_TOOLCHAIN_VERSION=clang \
         -DJSONCPP_WITHPOST_BUILD_UNITTEST=False \
         -DJSONCPP_WITH_TESTS=False
make -j 8 && make install

cd ../../../../



