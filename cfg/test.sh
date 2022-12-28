#!/bin/bash

SCRIPT_DIR=$( cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )
cd $SCRIPT_DIR/../build
make --no-print-directory

full_path=$SCRIPT_DIR/../test/runs/$(date "+%F-%T")
mkdir -p $full_path
pass_path=$(cd $full_path; pwd)
echo Test Saved at: $pass_path

MODEL_PATH=$SCRIPT_DIR/../weights/yolov5s.onnx
CLASSES_PATH=$SCRIPT_DIR/../weights/coco_classes.txt
TEST_IMAGE_PATH=$SCRIPT_DIR/../test/coco_test.jpg

./tests $pass_path $MODEL_PATH $CLASSES_PATH $TEST_IMAGE_PATH