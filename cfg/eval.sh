#!/bin/bash

SCRIPT_DIR=$( cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )
source $SCRIPT_DIR/.env.eval
cd $SCRIPT_DIR/../build
make --no-print-directory

if [[ -z "$SAVE_PATH" || -z "$MODEL_PATH" || -z "$CLASS_PATH" || -z "$IMAGES_PATH" ]];
then
    echo Ensure all parameters in ".env.eval" are setup
    exit 0
fi
./eval $SAVE_PATH $MODEL_PATH $CLASS_PATH $IMAGES_PATH
