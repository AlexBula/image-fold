#include <iostream>
#include <thread>
#include <atomic>
#include <mutex>
#include <algorithm>

#include "img-transform.h"

using namespace dlib;


/********** GLOBAL VARIABLES *********/
std::vector<std::mutex> D_Mutex(NR_P * NC_P); 
/************************************/


int from_2D_to_1D(int x, int y) {
    return x + (y * NR_P);
}


/* Calculate rgb distance between two pixels */
void rgb_distance(array2d<rgb_pixel> &img, int x, int y, int i, int j, 
        int &red, int &green, int &blue) {

    red += std::abs(img[x][y].red - img[i][j].red);
    green += std::abs(img[x][y].green - img[i][j].green);
    blue += std::abs(img[x][y].blue - img[i][j].blue);
}


void compare_distance(array2d<rgb_pixel> &img, int i, int j, int dist, array2d<rgb_pixel> &result, std::vector<int> &distance_array) {

    std::unique_lock<std::mutex> distance_lock(D_Mutex[from_2D_to_1D(i, j)]);
    if (distance_array[from_2D_to_1D(i, j)] < dist) {

        distance_array[from_2D_to_1D(i, j)] = dist;
        /* Save pixel in result image */
        result[i-PADDING][j-PADDING].red = img[i][j].red;
        result[i-PADDING][j-PADDING].green = img[i][j].green;
        result[i-PADDING][j-PADDING].blue = img[i][j].blue;
    }
    distance_lock.unlock();
}


void compute_distance(array2d<rgb_pixel> &img, int x, int y, array2d<rgb_pixel> &result, std::vector<int> &distance_array) {

    int dist; 
    int red = 0, green = 0, blue = 0;

    /* Iterate over all neighbours and compute distance */
    for(int i = x - 1; i <= x + 1; ++i){
        for(int j = y - 1; j <= y + 1; ++j){
            if (i != y && j != y) rgb_distance(img, x, y, i, j, red, green, blue);
        }
    }

    red /= 8;
    green /= 8; 
    blue /= 8;
    dist = (red + green + blue) / 3; 
    compare_distance(img, x, y, dist, result, distance_array);
}


array2d<rgb_pixel> add_padding(array2d<rgb_pixel> &img) {

    int no_cols = NC + (PADDING * 2), no_rows = NR + (PADDING * 2);
    array2d<rgb_pixel> new_image(no_rows, no_cols);
    for(int i = PADDING; i < NR; ++i) {
        for(int j = PADDING; j < NC; ++j) {
            new_image[i][j] = img[i][j];
        }
    }
    /* Omited pixels have default value -> 0,0,0 */
    return new_image;
}


/* Process single image */
void process_image(const std::string img_name, array2d<rgb_pixel> &result, 
        std::vector<int> &distance_array, int index, int no_images) {

    array2d<rgb_pixel> img;
    load_png(img, img_name);
    img = add_padding(img);

    /* For each pixel compute its distance to neighbours */
    for(int i = PADDING; i < NR; ++i) {
        for(int j = PADDING; j < NC; ++j){
            compute_distance(img, i, j, result, distance_array);
        }
    }
}


/* Get all image names from directory */
bool get_images(std::vector<std::string> &filenames) {

    DIR *dirp = opendir("data");
    if (dirp == NULL) return false;

    struct dirent *dp;
    while ((dp = readdir(dirp)) != NULL) {
        std::string name = DATA_LOC;
        name += dp->d_name;
        if (dp->d_name != "result.png" && name.find(".png") != std::string::npos) filenames.push_back(name); 
    }
    closedir(dirp);

    if (filenames.size() == 0) return false;
    else {
        std::sort(filenames.begin(), filenames.end()); 
        return true;
    }
}


