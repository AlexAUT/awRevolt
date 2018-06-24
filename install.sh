#!/bin/bash
ROOT_DIR=$(dirname "$0")

#Prepare extlibs
mkdir -p extlibs/include
mkdir -p extlibs/lib

# GLM
git clone https://github.com/g-truc/glm.git extlibs/glm
cp -r extlibs/glm/glm extlibs/include/

# SFML
git clone https://github.com/alexaut/sfml extlibs/sfml
mkdir -p extlibs/sfml/build
cd extlibs/sfml/build/
# Build sfml for all desktop types
mkdir debugShared
cd debugShared
cmake ../../ -DCMAKE_BUILD_TYPE=Debug -DCMAKE_INSTALL_PREFIX=../../../ -DBUILD_SHARED_LIBS=True 
make -j 8 && make install
cd ..
mkdir debugStatic
cd debugStatic
cmake ../../ -DCMAKE_BUILD_TYPE=Debug -DCMAKE_INSTALL_PREFIX=../../../ -DBUILD_SHARED_LIBS=False 
make -j 8 && make install
cd ..
mkdir releaseShared
cd releaseShared
cmake ../../ -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=../../../ -DBUILD_SHARED_LIBS=True 
make -j 8 && make install
cd ..
mkdir releaseStatic
cd releaseStatic
cmake ../../ -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=../../../ -DBUILD_SHARED_LIBS=False 
make -j 8 && make install
cd ..
cd ../../../

# Assimp
git clone https://github.com/assimp/assimp extlibs/assimp
mkdir -p extlibs/assimp/build 
cd extlibs/assimp/build
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
git clone https://github.com/open-source-parsers/jsoncpp extlibs/jsoncpp
mkdir -p extlibs/jsoncpp/buildDebug
mkdir -p extlibs/jsoncpp/buildRelease
cd extlibs/jsoncpp/buildRelease
cmake .. -DCMAKE_BUILD_TYPE=Release \
         -DCMAKE_INSTALL_PREFIX=../../ \
make -j 8 && make install
cd ../buildDebug
cmake .. -DCMAKE_BUILD_TYPE=Debug \
         -DCMAKE_INSTALL_PREFIX=../../ \
         -DDEBUG_LIBNAME_SUFFIX=-d
make -j 8 && make install

cd ../../../



