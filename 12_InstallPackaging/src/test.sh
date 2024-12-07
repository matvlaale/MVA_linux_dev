#!/bin/bash

cd build
ctest -V || exit 1
