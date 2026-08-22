#!/bin/bash

echo "Building..."

cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug
cmake --build build --clean-first

echo "Running..."

./build/ESP32ish