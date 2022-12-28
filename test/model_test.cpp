#include "catch.hpp"
#include "model.hpp"

bool test_annotations(std::string path)
{
    Model* net = new Model("/home/bliggett/cpp-cv/weights/yolov5s.onnx", "/home/bliggett/cpp-cv/weights/coco_classes.txt", false);
    if (strcmp(net->class_list[0] == "person")==0)
    {
        return true;
    }
    return false;
}
