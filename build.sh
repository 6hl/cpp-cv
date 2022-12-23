#!/bin/bash

if [ ! -d $SCRIPT_DIR/yolov5 ]; then
    mkdir build
fi
cd build
cmake -DCMAKE_PREFIX_PATH=/home/bliggett/opencv-4.x ..
cmake --build . --config Release

./detection