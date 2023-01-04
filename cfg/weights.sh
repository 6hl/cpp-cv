#!/bin/bash

SCRIPT_DIR=$( cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )
source $SCRIPT_DIR/.env.setup
cd $SCRIPT_DIR/../weights

if [ ! -d $PWD/yolov5 ]; then
    git clone https://github.com/ultralytics/yolov5.git
fi

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
        # pip3 install torch==1.11 # Torch <= 1.11 needed for onnx conversion
    fi
elif [ $ENV_TYPE == "venv" ]; then
    echo venv not setup
    exit 1
else
    echo ENV_TYPE must be `conda` or `venv`
    exit 1
fi
cd yolov5
# If opencv error: sudo apt-get install libgl1
python3 export.py --weights $MODEL_TYPE.pt --img $HEIGHT $WIDTH --batch 1 --include "onnx" --simplify --opset 12
# python3 export.py --weights $MODEL_TYPE.pt --include "onnx" #--simplify
mv $MODEL_TYPE.onnx $PWD/..