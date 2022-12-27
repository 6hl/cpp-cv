#include <fstream>

#include "model.hpp"

Model::Model(std::string model_path, std::string class_list_path, bool cuda)
{
    set_model(model_path, cuda);
    set_class_list(class_list_path);
}

void Model::set_model(std::string model_path, bool cuda){
    this->net = cv::dnn::readNet(model_path);
    if (cuda){
        net.setPreferableBackend(cv::dnn::DNN_BACKEND_CUDA);
        net.setPreferableTarget(cv::dnn::DNN_TARGET_CUDA_FP16);
    } else {
        net.setPreferableBackend(cv::dnn::DNN_BACKEND_OPENCV);
        net.setPreferableTarget(cv::dnn::DNN_TARGET_CPU);
    }
}

void Model::set_class_list(std::string class_list_path){
    std::ifstream ifs(class_list_path);
    std::string fline;
    while (std::getline(ifs, fline))
    {
        this->class_list.push_back(fline);
    }
}