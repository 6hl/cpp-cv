#ifndef _DETECTOR_
#define _DETECTOR_
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
void nms(std::vector<cv::Rect> bboxs, std::vector<float> confidences, float SCORE_THRESH, float NMS_THRESH, std::vector<Object> &output);
void detect(cv::Mat &img, Model& model, std::vector<Object>& output, const std::vector<std::string>& classNames);
#endif
