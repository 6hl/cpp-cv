#!/bin/bash
export MAKEFLAGS=--no-print-directory
SCRIPT_DIR=$( cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )
source $SCRIPT_DIR/.env.setup

if [ ! -d $SCRIPT_DIR/../build ]; then
    mkdir build
fi
cd build
cmake -DCMAKE_PREFIX_PATH=$OPENCV_PATH ..
cmake --build . --config Release
