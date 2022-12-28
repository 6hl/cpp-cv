#include "detector.hpp"
#include "utils.hpp"
#include <sstream>

int main(int argc, char** argv){
    std::string RUN_DIR = argv[1];
    std::string MODEL_PATH = argv[2];
    std::string CLASSES_PATH = argv[3];
    std::string TEST_IMAGE_PATH = argv[4];

    std::ostringstream image_save_path;

    Model* net = new Model(MODEL_PATH, CLASSES_PATH, false);
    cv::Mat image = cv::imread(TEST_IMAGE_PATH, cv::IMREAD_COLOR);
    std::vector<Object> detections;
    detect(image, net, detections, net->class_list);

    auto new_image = plot_bboxs(image, detections, net->class_list);
    
    image_save_path << RUN_DIR << "/" << "res.jpg";
    std::cout << image_save_path.str() << std::endl;
    cv::imwrite(image_save_path.str(), new_image);
    return 0;
}