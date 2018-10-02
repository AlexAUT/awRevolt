set -e

mkdir -p build
cd build
cmake -DCMAKE_BUILD_TYPE=Debug -DAW_BUILD_TEST=false -DCMAKE_INSTALL_PREFIX=/usr/local/ ..
make -j 8
sudo make install
cd ..
