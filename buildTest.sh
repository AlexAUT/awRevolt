set -e

mkdir -p build
cd build
cmake -DCMAKE_BUILD_TYPE=Debug -DAW_BUILD_TEST=true ..
make -j 8
cd ..
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/usr/local/lib/
build/awRevolt
