#ifndef _CPP_BL_UTILS_
#define _CPP_BL_UTILS_

// #include <opencv2/opencv.hpp>
#include "detector.hpp"
#include <filesystem>
#include <iterator>

const std::vector<cv::Scalar> COLORS = {cv::Scalar(255, 255, 0), cv::Scalar(0, 255, 0), cv::Scalar(0, 255, 255), cv::Scalar(255, 0, 0)};
cv::Mat plot_bboxs(cv::Mat base_image, std::vector<Object> detections, std::vector<std::string> class_list);

class Dataset
{
    private:
        std::filesystem::directory_iterator fnames;
    public:
        Dataset(std::string dataset_directory);
        cv::Mat sample();
        int length;
};

#endif