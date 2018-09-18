set -e

#Download dependencies
./downloadExtlibs.sh

#!/bin/bash
ROOT_DIR=$(dirname "$0")

#install glm
cp -r extlibs/glm/glm extlibs/include/

# Build SFML
mkdir -p extlibs/sfml/buildDesktop
cd extlibs/sfml/buildDesktop
# Build sfml for all desktop types
mkdir -p debugShared
cd debugShared
cmd "/C cmake ../../ -G "MinGW Makefiles" -DCMAKE_BUILD_TYPE=Debug -DCMAKE_INSTALL_PREFIX=../../../ -DBUILD_SHARED_LIBS=True" 
cmd "/C mingw32-make -j8"
cmd "/C mingw32-make install"
cd ..
mkdir -p debugStatic
cd debugStatic
cmd "/C cmake ../../ -G "MinGW Makefiles" -DCMAKE_BUILD_TYPE=Debug -DCMAKE_INSTALL_PREFIX=../../../ -DBUILD_SHARED_LIBS=False"
cmd "/C mingw32-make -j8"
cmd "/C mingw32-make install"
cd ..
mkdir -p releaseShared
cd releaseShared
cmd "/C cmake ../../ -G "MinGW Makefiles" -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=../../../ -DBUILD_SHARED_LIBS=True"
cmd "/C mingw32-make -j8"
cmd "/C mingw32-make install"
cd ..
mkdir -p releaseStatic
cd releaseStatic
cmd "/C cmake ../../ -G "MinGW Makefiles" -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=../../../ -DBUILD_SHARED_LIBS=False"
cmd "/C mingw32-make -j8"
cmd "/C mingw32-make install"
cd ..
cd ../../../

# Build Assimp
mkdir -p extlibs/assimp/buildDesktop
cd extlibs/assimp/buildDesktop
cmd "/C cmake ..  -G "MinGW Makefiles" -DCMAKE_BUILD_TYPE=Debug \
         -DCMAKE_INSTALL_PREFIX=../../ \
         -DASSIMP_BUILD_ALL_IMPORTERS_BY_DEFAULT=False \
         -DASSIMP_BUILD_TESTS=False \
         -DASSIMP_BUILD_SAMPLES=False \
         -DASSIMP_BUILD_OBJ_IMPORTER=True \
         -DASSIMP_BUILD_FBX_IMPORTER=True \
         -DASSIMP_BUILD_COLLADA_IMPORTER=True \
         -DASSIMP_BUILD_ASSIMP_TOOLS=False"
         
cmd "/C mingw32-make -j8"
cmd "/C mingw32-make install"
cd ../../../

# JSONCPP
mkdir -p extlibs/jsoncpp/buildDesktop
cd extlibs/jsoncpp/buildDesktop
mkdir -p release
cd release
cmd "/C cmake ../..  -G "MinGW Makefiles" -DCMAKE_BUILD_TYPE=Release \
         -DCMAKE_INSTALL_PREFIX=../../../"
cmd "/C mingw32-make -j8"
cmd "/C mingw32-make install"
cd ..
mkdir -p debug
cd debug
cmd "/C cmake ../..  -G "MinGW Makefiles" -DCMAKE_BUILD_TYPE=Debug \
         -DCMAKE_INSTALL_PREFIX=../../../ \
         -DDEBUG_LIBNAME_SUFFIX=-d"
cmd "/C mingw32-make -j8"
cmd "/C mingw32-make install"
cd ../../../../



