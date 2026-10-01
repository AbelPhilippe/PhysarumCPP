#!/bin/bash

set -e

rm -rf build

mkdir build
cd build

cmake ..
cmake --build .

echo "Now u can run"