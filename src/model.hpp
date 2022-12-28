#ifndef _CPP_CV_MODEL_
#define _CPP_CV_MODEL_

#include <opencv2/opencv.hpp>
#include <string>
#include <vector>

struct Model
{
    Model(std::string model_path, std::string class_list_path, bool cuda);
    void set_model(std::string model_path, bool cuda);
    void set_class_list(std::string class_list_path);

    std::vector<std::string> class_list;
    cv::dnn::Net net;
};

#endif