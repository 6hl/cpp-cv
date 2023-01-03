#include "utils.hpp"

cv::Mat plot_bboxs(cv::Mat base_image, std::vector<Object> detections, std::vector<std::string> class_list)
{
    auto result_image = base_image.clone();
    for (auto& object : detections)
    {
        auto bbox = object.bbox;
        auto class_id = object.class_id;
        const auto color = COLORS[class_id % COLORS.size()];

        cv::rectangle(result_image, bbox, color, 2);
        if ((bbox.x + bbox.width) > 400)
        {
            auto x_max = cv::getTextSize(class_list[class_id].c_str(), cv::FONT_HERSHEY_SIMPLEX, 0.3, 1, 0);
            cv::rectangle(result_image, cv::Point(bbox.x, bbox.y-15), cv::Point(bbox.x+x_max.width, bbox.y), color, cv::FILLED);
            cv::putText(result_image, class_list[class_id].c_str(), cv::Point(bbox.x, bbox.y - 5), cv::FONT_HERSHEY_SIMPLEX, 0.3, cv::Scalar(0, 0, 0));
        }
    }
    return result_image;
}

void save_plot(cv::Mat image, std::string path)
{
    cv::imwrite(path, image);
    std::cout << "Saved image at "+path << std::endl;
}

Dataset::Dataset(std::string dataset_directory)
    : fnames(dataset_directory),
      ds_length(std::distance(std::filesystem::directory_iterator(dataset_directory), 
                           std::filesystem::directory_iterator{}))
    {
    }

cv::Mat Dataset::sample()
{
    current_fname = (*fnames).path().filename();
    cv::Mat image = cv::imread((*fnames).path(), cv::IMREAD_COLOR);
    fnames++;
    return image;
}

int Dataset::length(){return ds_length;}
std::string Dataset::file_name(){return current_fname;}
