: "${ANDROID_NDK:?Need to set ANDROID_NDK to the NDK root directory}"

ROOT_DIR="$( cd "$(dirname "$0")" ; pwd -P )"

BUILD_DIR=/tmp/androidBuild
mkdir -p $BUILD_DIR

#cleanup old build log
LOG_FILE=$BUILD_DIR/log.txt
rm -f $LOG_FILE

#default android cmake paramters
CMAKE_PARAMS="-DBUILD_SHARED_LIBS=True \
-DBUILD_SHARED_LIBS=True \
-DCMAKE_SYSTEM_NAME=Android -DCMAKE_ANDROID_NDK=$ANDROID_NDK \
-DCMAKE_INSTALL_PREFIX=$ANDROID_NDK/sources/third_party \
-DCMAKE_ANDROID_STL_TYPE=c++_shared -DCMAKE_ANDROID_NDK_TOOLCHAIN_VERSION=clang"


#GLM, glm forced the source directory to be inside the repo...
cd $ROOT_DIR/glm
echo "Configure GLM..."
cmake $ROOT_DIR/glm -DCMAKE_BUILD_TYPE=Debug \
                    $CMAKE_PARAMS \
                    -DGLM_TEST_ENABLE=False \
                    &>> $LOG_FILE
echo "Build GLM..."
make -j &>> $LOG_FILE
echo "Install GLM..."
make install &>> $LOG_FILE
cd $ROOT_DIR

#ASSIMP
ASSIMP_BUILD_DIR=$BUILD_DIR/assimp
mkdir -p $ASSIMP_BUILD_DIR && cd $ASSIMP_BUILD_DIR

for buildType in Debug Release; do
  mkdir -p $ASSIMP_BUILD_DIR/$buildType && cd $ASSIMP_BUILD_DIR/$buildType

  echo "Configure Assimp $buildType..."
  cmake $ROOT_DIR/assimp -DCMAKE_BUILD_TYPE=$buildType \
                         $CMAKE_PARAMS \
                         -DASSIMP_LIB_INSTALL_DIR=lib/armeabi-v7a
                         -DASSIMP_BUILD_ALL_IMPORTERS_BY_DEFAULT=True \
                         -DASSIMP_BUILD_TESTS=False \
                         -DASSIMP_BUILD_SAMPLES=False \
                         -DASSIMP_BUILD_OBJ_IMPORTER=True \
                         -DASSIMP_BUILD_FBX_IMPORTER=True \
                         -DASSIMP_BUILD_COLLADA_IMPORTER=True \
                         -DASSIMP_BUILD_ASSIMP_TOOLS=False \
                         &>> $LOG_FILE

  echo "Build Assimp $buildType..."
  make -j &>> $LOG_FILE
  echo "Install Assimp $buildType..."
  make install &>> $LOG_FILE

done

cd $ROOT_DIR

#SFML
SFML_BUILD_DIR=$BUILD_DIR/sfml
mkdir -p $SFML_BUILD_DIR && cd $SFML_BUILD_DIR

for buildType in Debug Release; do
  mkdir -p $SFML_BUILD_DIR/$buildType && cd $SFML_BUILD_DIR/$buildType

  echo "Configure SFML $buildType..."
  cmake $ROOT_DIR/sfml   -DCMAKE_BUILD_TYPE=$buildType \
                         $CMAKE_PARAMS \
                         &>> $LOG_FILE

  echo "Build SFML $buildType..."
  make -j &>> $LOG_FILE
  echo "Install SFML $buildType..."
  make install &>> $LOG_FILE

done

#JSONCPP
JSONCPP_BUILD_DIR=$BUILD_DIR/jsoncpp
mkdir -p $JSONCPP_BUILD_DIR && cd $JSONCPP_BUILD_DIR

for buildType in Debug Release; do
  mkdir -p $JSONCPP_BUILD_DIR/$buildType && cd $JSONCPP_BUILD_DIR/$buildType

  echo "Configure jsoncpp $buildType..."
  cmake $ROOT_DIR/jsoncpp   -DCMAKE_BUILD_TYPE=$buildType \
                         $CMAKE_PARAMS \
                         -DCMAKE_INSTALL_LIBDIR=lib/armeabi-v7a \
                         -DDEBUG_LIBNAME_SUFFIX=d \
                         -DBUILD_STATIC_LIBS=False \
                         -DJSONCPP_WITHPOST_BUILD_UNITTEST=False \
                         -DJSONCPP_WITH_TESTS=False \
                         &>> $LOG_FILE

  echo "Build jsoncpp $buildType..."
  make -j &>> $LOG_FILE
  echo "Install jsoncpp $buildType..."
  make install &>> $LOG_FILE

done

cd $ROOT_DIR

