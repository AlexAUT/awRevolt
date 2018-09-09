set -e

#!/bin/bash
ROOT_DIR=$(dirname "$0")

#Prepare extlibs
mkdir -p extlibs/include
mkdir -p extlibs/lib

# GLM
FOLDER=extlibs/glm
URL=https://github.com/g-truc/glm.git
if [ ! -d "$FOLDER" ] ; then
  git clone $URL $FOLDER
else
  (cd "$FOLDER" && git pull $URL)
fi

#sfml
FOLDER=extlibs/sfml
URL=https://github.com/alexaut/sfml
if [ ! -d "$FOLDER" ] ; then
  git clone $URL $FOLDER
else
  (cd "$FOLDER" && git pull $URL)
fi

#Assimp
FOLDER=extlibs/assimp
URL=https://github.com/alexaut/assimp
if [ ! -d "$FOLDER" ] ; then
  git clone $URL $FOLDER
else
  (cd "$FOLDER" && git pull $URL)
fi

#JSONCPP
FOLDER=extlibs/jsoncpp
URL=https://github.com/open-source-parsers/jsoncpp
if [ ! -d "$FOLDER" ] ; then
  git clone $URL $FOLDER
else
  (cd "$FOLDER" && git pull $URL)
fi

