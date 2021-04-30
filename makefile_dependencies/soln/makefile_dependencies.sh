#!/bin/bash
g++ makefile_dependencies.cpp -o makefile_dependencies -Wall -std=c++11 -O2 && ./makefile_dependencies
rm -f ./makefile_dependencies
