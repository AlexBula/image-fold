#include <thread>

#include "img-transform.h"

using namespace dlib;


int main(int argc, char *argv[]) {
   
    if (argc != 2) {
        std::cerr << "Error, usage: " << argv[0] << " data_location\n";
        return 1;
    }
    
    std::string data_loc = argv[1];
    auto result = array2d<rgb_pixel>(NR, NC);
    auto depth_map = array2d<rgb_pixel>(NR,NC);
    std::vector<int> distance_array(NR_P * NC_P, 0); 
    std::vector<int> picture_ids(NR_P * NC_P, 0);
    std::vector<std::string> filenames; 
    
    if (!get_images(filenames, data_loc)) {
        std::cerr << "Error with directory: " << data_loc << "\n";
        std::cerr << "Please provide correct data location and make sure it is not empty.\n";
        return 1;
    }

    std::thread threads[filenames.size()];

    for(uint i = 0; i < filenames.size(); ++i) {
        threads[i] = std::thread(process_image, filenames[i], 
                std::ref(result), std::ref(distance_array), 
                std::ref(picture_ids), i, filenames.size());
    }

    for(uint i = 0; i < filenames.size(); ++i) 
        threads[i].join();

    draw_depth_map(depth_map, picture_ids, filenames.size());

    save_png(result, "focused_image.png");
    save_png(depth_map, "depth_map.png");

    return 0;
}




