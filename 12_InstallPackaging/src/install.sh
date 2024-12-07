#!/bin/bash

mkdir build
cd build
cmake -DENABLE_TESTS=OFF ..
make
sudo make install
cd ..
