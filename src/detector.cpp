#include "detector.hpp"

cv::Mat format_img(const cv::Mat& img)
{
    int col = img.cols;
    int row = img.rows;
    int _max = MAX(col, row);
    cv::Mat resized = cv::Mat::zeros(_max, _max, CV_8UC3);
    img.copyTo(resized(cv::Rect(0, 0, col, row)));

    cv::Mat res;
    cv::dnn::blobFromImage(img, res, 1./255., cv::Size(640, 640), cv::Scalar(), true, false);
    return res;
}

cv::Rect to_yolo(float* data, float x_f, float y_f)
{
    float x = data[0];
    float y = data[1];
    float w = data[2];
    float h = data[3];
    int left = int((x - 0.5 * w) * x_f);
    int top = int((y - 0.5 * h) * y_f);
    int width = int(w * x_f);
    int height = int(h * y_f);
    return cv::Rect(left, top, width, height);
}

void nms(std::vector<cv::Rect> bboxs, std::vector<float> confidences, std::vector<int> class_ids, float SCORE_THRESH, float NMS_THRESH, std::vector<Object>& output)
{
    std::vector<int> nms_result;
    cv::dnn::NMSBoxes(bboxs, confidences, SCORE_THRESH, NMS_THRESH, nms_result);
    for (int i = 0; i < nms_result.size(); ++i) {
        int idx = nms_result[i];
        Object result;
        result.class_id = class_ids[idx];
        result.confidence = confidences[idx];
        result.bbox = bboxs[idx];
        output.push_back(result);
    }
}

void detect(cv::Mat& img, Model* model, std::vector<Object>& output, const std::vector<std::string>& classNames)
{
    cv::Mat blob;
    auto conv_img = format_img(img);
    model->net.setInput(conv_img);
    std::vector<cv::Mat> m_output;
    model->net.forward(m_output, model->net.getUnconnectedOutLayersNames());

    float x_f = img.cols / 640.;
    float y_f = img.rows / 640.;
    float *data = (float *)m_output[0].data;

    const int dimensions = 85;
    const int rows = 25200;

    std::vector<int> class_ids;
    std::vector<float> confidences;
    std::vector<cv::Rect> bboxs;

    for (int i = 0; i < rows; ++i)
    {
        float confidence = data[4];
        if (confidence >= 0.4) // CONFIDENCE_THRESH
        {
            float* classes_scores = data + 5;
            cv::Mat scores(1, classNames.size(), CV_32FC1, classes_scores);
            cv::Point class_id;
            double max_class_score;
            cv::minMaxLoc(scores, 0, &max_class_score, 0, &class_id);

            if (max_class_score > 0.2) // SCORE_THRESH
            {
                confidences.push_back(confidence);
                class_ids.push_back(class_id.x);
                bboxs.push_back(to_yolo(data, x_f, y_f));
            }
        }
        data += 85;  
    }
    nms(bboxs, confidences, class_ids, 0.4, .4, output);
}
