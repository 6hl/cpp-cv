#include "utils.hpp"

cv::Mat plot_bboxs(cv::Mat base_image, std::vector<Object> detections, std::vector<std::string> class_list)
{
    auto result_image = base_image.clone();
    for (int i = 0; i < detections.size(); ++i)
    {
        auto object = detections[i];
        auto bbox = object.bbox;
        auto class_id = object.class_id;
        const auto color = COLORS[class_id % COLORS.size()];

        cv::rectangle(result_image, bbox, color, 3);
        cv::rectangle(result_image, cv::Point(bbox.x, bbox.y-20), cv::Point(bbox.x + bbox.width, bbox.y), color, cv::FILLED);
        cv::putText(result_image, class_list[class_id].c_str(), cv::Point(bbox.x, bbox.y - 5), cv::FONT_HERSHEY_SIMPLEX, 0.5, cv::Scalar(0, 0, 0));
    }
    return result_image;
}

Dataset::Dataset(std::string dataset_directory)
    : fnames(dataset_directory),
      length(std::distance(std::filesystem::directory_iterator(dataset_directory), 
                           std::filesystem::directory_iterator{}))
    {
    }

cv::Mat Dataset::sample()
{
    cv::Mat image = cv::imread((*fnames).path(), cv::IMREAD_COLOR);
    fnames++;
    return image;
}
