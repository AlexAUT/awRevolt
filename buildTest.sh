set -e

mkdir -p build
cd build
cmake -DCMAKE_BUILD_TYPE=Debug -DAW_BUILD_TEST=true ..
make -j 8
cd ..
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/usr/local/lib/
if [ $1 -gt 1 ]
then
  apitrace trace build/awRevolt
elif [ $1 -gt 0 ]
then
  gdb build/awRevolt
else
  build/awRevolt
fi
