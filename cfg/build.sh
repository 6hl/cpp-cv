#!/bin/bash
export MAKEFLAGS=--no-print-directory
SCRIPT_DIR=$( cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )
if [ ! -d $SCRIPT_DIR/.. ]; then
    mkdir build
fi
cd build
cmake -DCMAKE_PREFIX_PATH=/home/bliggett/opencv-4.x ..
cmake --build . --config Release
