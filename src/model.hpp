#ifndef _FRCNN_
#define _FRCNN_

#include <opencv2/opencv.hpp>
#include <string>
#include <vector>

class Model
{
    private:
        cv::dnn::Net net;

    public:
        Model(std::string model_path, std::string class_list_path, bool cuda);
        ~Model(){ }
        void set_model(std::string model_path, bool cuda);
        void set_class_list(std::string class_list_path);
        std::vector<std::string> class_list;

};

#endif