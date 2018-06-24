set -e

mkdir -p build
cd build
cmake -DCMAKE_BUILD_TYPE=Debug -DAW_BUILD_TEST=false -DCMAKE_INSTALL_PREFIX=../extlibs/ ..
make -j 8
make install
cd ..
