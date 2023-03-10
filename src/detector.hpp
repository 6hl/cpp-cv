#ifndef _CPP_CV_DETECTOR_
#define _CPP_CV_DETECTOR_

#include <opencv2/opencv.hpp>
#include <string>
#include <vector>

#include "model.hpp"

struct Object
{
    int class_id;
    float confidence;
    cv::Rect bbox;
    std::string fname;
};

cv::Mat format_img(const cv::Mat &img);
cv::Rect to_yolo(float data, float x_f, float y_f);
std::vector<Object> nms(std::vector<cv::Rect> bboxs, std::vector<float> confidences, float SCORE_THRESH, float NMS_THRESH);
std::vector<Object> detect(cv::Mat& img, Model* model, const std::vector<std::string>& classNames);
#endif
