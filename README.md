# c++ Live Object Detection using onnx

## Getting started

### Prerequisites

[Install OpenCV for C++](https://docs.opencv.org/4.x/d7/d9f/tutorial_linux_install.html)

Clone the repo:  
```
git clone https://github.com/6hl/cpp-cv.git
```

### Setup repo
```
./build.sh
./weights/build_weights.sh <ENV_TYPE> <MODEL_TYPE> <HEIGHT> <WIDTH>
```
> where ENV_TYPE is `conda` or `venv`, MODEL_TYPE is any yolov5 variant, and HEIGHT/WIDTH are image input height and width.
