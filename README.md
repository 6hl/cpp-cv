# c++ Live Object Detection using onnx

## Getting started

### Prerequisites

[Install OpenCV for C++](https://docs.opencv.org/4.x/d7/d9f/tutorial_linux_install.html)

Clone the repo:  
```
git clone https://github.com/6hl/cpp-cv.git
```

### Setup repo

Adjust `cfg/.env.setup` for requested configuration. Make sure to set `OPENCV_PATH`
```
make build
make weights
```  

Then for evaluation on folder of images
```
make eval
```  

* TODO: setup live inference with `make run`