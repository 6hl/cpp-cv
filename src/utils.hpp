#ifndef _CPP_CV_UTILS_
#define _CPP_CV_UTILS_

#include <opencv2/opencv.hpp>
#include "detector.hpp"

const std::vector<cv::Scalar> COLORS = {cv::Scalar(255, 255, 0), cv::Scalar(0, 255, 0), cv::Scalar(0, 255, 255), cv::Scalar(255, 0, 0)};
cv::Mat plot_bboxs(cv::Mat base_image, std::vector<Object> detections, std::vector<std::string> class_list);

#endif