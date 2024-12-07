#!/bin/bash

mkdir build
cd build
cmake -DENABLE_TESTS=ON ..
make
cd ..
