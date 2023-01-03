#ifndef _CPP_CV_UTILS_
#define _CPP_CV_UTILS_

#include <opencv2/opencv.hpp>
#include <filesystem>
#include <iterator>
#include <string>
#include <vector>

#include "detector.hpp"

const std::vector<cv::Scalar> COLORS = {
    cv::Scalar(240, 80, 80), cv::Scalar(0, 255, 255), cv::Scalar(0, 0, 255)};
cv::Mat plot_bboxs(cv::Mat base_image, std::vector<Object> detections, std::vector<std::string> class_list);
void save_plot(cv::Mat image, std::string path);

class Dataset
{
    public:
        Dataset(std::string dataset_directory);
        cv::Mat sample();
        int length();
        std::string file_name();
        
    private:
        std::filesystem::directory_iterator fnames;
        int ds_length;
        std::string current_fname;
};

#endif