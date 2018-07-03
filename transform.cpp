#include <thread>

#include "img-transform.h"

using namespace dlib;


int main(void) {
    
    auto result = array2d<rgb_pixel>(NR, NC);
    std::vector<int> distance_array(NR_P * NC_P, 0); 
   
    std::vector<std::string> filenames; 
    if (!get_images(filenames)) {
        std::cerr << "Error with directory: " << DATA_LOC << "\n";
        std::cerr << "Please provide correct data location and make sure it is not empty.\n";
        return 1;
    }

    std::thread threads[filenames.size()];

    for(int i = 0; i < filenames.size(); ++i) {
        threads[i] = std::thread(process_image, filenames[i], 
                std::ref(result), std::ref(distance_array), i, filenames.size());
    }

    for(int i = 0; i < filenames.size(); ++i) 
        threads[i].join();

    save_png(result, "r.png");

    return 0;
}




