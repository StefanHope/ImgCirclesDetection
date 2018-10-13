#! /bin/bash
echo inside make.sh 
mkdir -p /ImgCirclesDetection/build
cd /ImgCirclesDetection/build
cmake ../src
make && ./runTests
