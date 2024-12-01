#!/bin/bash

mkdir build
cd build
cmake -DCMAKE_INSTALL_PREFIX=.. ..
make && make install
cd ..
doxygen Doxyfile
