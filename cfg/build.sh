#!/bin/bash
export MAKEFLAGS=--no-print-directory
SCRIPT_DIR=$( cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )
source $SCRIPT_DIR/.env

if [ ! -d $SCRIPT_DIR/../build ]; then
    mkdir build
fi
cd build
cmake -DCMAKE_PREFIX_PATH=/home/bliggett/opencv-4.x ..
cmake --build . --config Release
