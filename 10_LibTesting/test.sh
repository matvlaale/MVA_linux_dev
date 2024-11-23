#!/bin/bash

cd build
ctest
lcov --capture --directory . --output-file coverage.info
genhtml coverage.info --output-directory coverage_report
mv coverage_report ..
echo -e "\nLook coverage report in project root directory!\n"
