ROOT_DIR="$( cd "$(dirname "$0")" ; pwd -P )"

INSTALL_DIR=$ROOT_DIR/built
mkdir -p built

BUILD_DIR=/tmp/linuxBuild
mkdir -p $BUILD_DIR

#cleanup old build log
LOG_FILE=$BUILD_DIR/log.txt
rm -f $LOG_FILE

#default cmake paramters
CMAKE_PARAMS="-DBUILD_SHARED_LIBS=True \
-DCMAKE_INSTALL_PREFIX=$INSTALL_DIR"


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

  echo "Configure Assimp $buildType may take a while..."
  cmake $ROOT_DIR/assimp -DCMAKE_BUILD_TYPE=$buildType \
                         $CMAKE_PARAMS \
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

