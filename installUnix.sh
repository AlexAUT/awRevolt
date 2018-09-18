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
cmake ../../ -DCMAKE_BUILD_TYPE=Debug -DCMAKE_INSTALL_PREFIX=../../../ -DBUILD_SHARED_LIBS=True 
make -j 8 && make install
cd ..
mkdir -p debugStatic
cd debugStatic
cmake ../../ -DCMAKE_BUILD_TYPE=Debug -DCMAKE_INSTALL_PREFIX=../../../ -DBUILD_SHARED_LIBS=False 
make -j 8 && make install
cd ..
mkdir -p releaseShared
cd releaseShared
cmake ../../ -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=../../../ -DBUILD_SHARED_LIBS=True 
make -j 8 && make install
cd ..
mkdir -p releaseStatic
cd releaseStatic
cmake ../../ -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=../../../ -DBUILD_SHARED_LIBS=False 
make -j 8 && make install
cd ..
cd ../../../

# Build Assimp
mkdir -p extlibs/assimp/buildDesktop
cd extlibs/assimp/buildDesktop
cmake .. -DCMAKE_BUILD_TYPE=Release \
         -DCMAKE_INSTALL_PREFIX=../../ \
         -DASSIMP_BUILD_ALL_IMPORTERS_BY_DEFAULT=False \
         -DASSIMP_BUILD_TESTS=False \
         -DASSIMP_BUILD_SAMPLES=False \
         -DASSIMP_BUILD_OBJ_IMPORTER=True \
         -DASSIMP_BUILD_FBX_IMPORTER=True \
         -DASSIMP_BUILD_COLLADA_IMPORTER=True
make -j 8 && make install
cd ../../../

# JSONCPP
mkdir -p extlibs/jsoncpp/buildDesktop
cd extlibs/jsoncpp/buildDesktop
mkdir -p release
cd release
cmake ../.. -DCMAKE_BUILD_TYPE=Release \
         -DCMAKE_INSTALL_PREFIX=../../../
make -j 8 && make install

cd ..
mkdir -p debug
cd debug
cmake ../.. -DCMAKE_BUILD_TYPE=Debug \
         -DCMAKE_INSTALL_PREFIX=../../../ \
         -DDEBUG_LIBNAME_SUFFIX=-d
make -j 8 && make install

cd ../../../../



