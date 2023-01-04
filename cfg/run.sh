#!/bin/bash

SCRIPT_DIR=$( cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )
source $SCRIPT_DIR/.env.run
cd $SCRIPT_DIR/../build
make --no-print-directory
./detection $SAVE_PATH $MODEL_PATH $CLASS_PATH $IMAGE_PATH