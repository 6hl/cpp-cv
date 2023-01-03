#include "detector.hpp"

cv::Mat format_img(const cv::Mat& img)
{
    int col = img.cols;
    int row = img.rows;
    int max = MAX(col, row);
    cv::Mat resized = cv::Mat::zeros(max, max, CV_8UC3);
    img.copyTo(resized(cv::Rect(0, 0, col, row)));

    cv::Mat res;
    cv::dnn::blobFromImage(img, res, 1./255., cv::Size(640, 640), cv::Scalar(), true, false);
    return res;
}

cv::Rect to_yolo(float* data, float x_scale, float y_scale)
{
    float x = data[0];
    float y = data[1];
    float w = data[2];
    float h = data[3];
    int scaled_x = int((x - 0.5 * w) * x_scale);
    int scaled_y = int((y - 0.5 * h) * y_scale);
    int scaled_w = int(w * x_scale);
    int scaled_h = int(h * y_scale);
    return cv::Rect(scaled_x, scaled_y, scaled_w, scaled_h);
}

std::vector<Object> nms(std::vector<cv::Rect> bboxs, std::vector<float> confidences, std::vector<int> class_ids, float SCORE_THRESH, float NMS_THRESH)
{
    std::vector<Object> detections;
    std::vector<int> nms_result;
    cv::dnn::NMSBoxes(bboxs, confidences, SCORE_THRESH, NMS_THRESH, nms_result);
    for (auto& idx : nms_result)
    {
        Object object;
        object.class_id = class_ids[idx];
        object.confidence = confidences[idx];
        object.bbox = bboxs[idx];
        detections.push_back(object);
    }
    return detections;
}

std::vector<Object> detect(cv::Mat& img, Model* model, const std::vector<std::string>& classNames)
{
    auto conv_img = format_img(img);
    model->net.setInput(conv_img);
    std::vector<cv::Mat> model_output;
    model->net.forward(model_output, model->net.getUnconnectedOutLayersNames());

    float x_scale = img.cols / 640.;
    float y_scale = img.rows / 640.;
    float* data = reinterpret_cast<float*>(model_output[0].data);
    const int rows = model_output[0].size[2];                           // 85 for yolov5
    const int cols = model_output[0].size[1];                           // 25200 for 640x640

    std::vector<int> class_ids;
    std::vector<float> confidences;
    std::vector<cv::Rect> bboxs;

    for (int i = 0; i < cols; ++i)
    {
        float confidence = data[4];
        if (confidence >= 0.4)                                          // CONFIDENCE_THRESH
        {
            cv::Mat scores(1, classNames.size(), CV_32FC1, data + 5); 
            cv::Point class_id;                                             
            double max_class_score;
            cv::minMaxLoc(scores, 0, &max_class_score, 0, &class_id);

            if (max_class_score > 0.2)                                  // SCORE_THRESH
            {
                confidences.push_back(confidence);
                class_ids.push_back(class_id.x);
                bboxs.push_back(to_yolo(data, x_scale, y_scale));
            }
        }
        data += rows;
    }
    return nms(bboxs, confidences, class_ids, 0.4, 0.4);
}