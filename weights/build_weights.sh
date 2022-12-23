#!/bin/bash

ENV_TYPE=$1
MODEL_TYPE=$2
HEIGHT=$3
WIDTH=$4
if [ -z "${MODEL_TYPE}" ]; then
    MODEL_TYPE=yolov5s
fi
if [ -z "${HEIGHT}" ]; then
    HEIGHT=640
fi
if [ -z "${WIDTH}" ]; then
    HEIGHT=640
fi

SCRIPT_DIR=$( cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )

cd $SCRIPT_DIR
if [ ! -d $SCRIPT_DIR/yolov5 ]; then
    git clone https://github.com/ultralytics/yolov5.git
fi
cd yolov5
if [ $ENV_TYPE == "conda" ]; then
    # IF ERROR CHANGE TO ~/anaconda3/bin/activate
    source ~/miniconda3/etc/profile.d/conda.sh
    conda init bash
    if { conda env list | grep 'yolo-env'; } >/dev/null 2>&1; 
    then 
        conda activate yolo-env
    else
        conda create -y -n yolo-env python=3.8
        conda activate yolo-env
        conda install -y pip
        pip3 install -r requirements.txt
    fi
    
elif [ $ENV_TYPE == "venv" ]; then
    echo venv not setup
    exit 1
else
    echo ENV_TYPE must be `conda` or `venv`
    exit 1
fi
# If opencv error: sudo apt-get install libgl1
python3 export.py --weights $MODEL_TYPE.pt --img $HEIGHT $WIDTH --batch 1 --include "onnx" --simplify
mv $MODEL_TYPE.onnx $SCRIPT_DIR
