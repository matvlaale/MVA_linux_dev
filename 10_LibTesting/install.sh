#!/bin/bash

mkdir build
cd build
cmake -DCODE_COVERAGE=ON ..
make
# make install
