#include "utils.hpp"
#include <sstream>
#include <chrono>

int main(int argc, char** argv){
    std::string SAVE_DIR = argv[1];
    std::string MODEL_PATH = argv[2];
    std::string CLASSES_PATH = argv[3];
    std::string IMAGES_PATH = argv[4];

    std::ostringstream image_save_path;

    Model* net = new Model(MODEL_PATH, CLASSES_PATH, false);
    Dataset dataset(IMAGES_PATH);
    for (int i=0; i <dataset.length(); ++i)
    {
        image_save_path.str("");
        image_save_path.clear();
        auto image = dataset.sample();
        auto start = std::chrono::high_resolution_clock::now();
        auto detections = detect(image, net, net->class_list);
        auto stop = std::chrono::high_resolution_clock::now();
        auto new_image = plot_bboxs(image, detections, net->class_list);
        image_save_path << SAVE_DIR << "/" << dataset.filename();
        save_plot(new_image, image_save_path.str());
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
        std::cout << duration.count() << std::endl;
    }
    delete net;
    return 0;
}