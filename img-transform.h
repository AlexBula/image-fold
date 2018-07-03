#ifndef IMG_TRANSFORM_H
#define IMG_TRANSFORM_H

#include <sys/types.h>
#include <dirent.h>
#include <dlib/image_io.h>
#include <dlib/array2d.h>
#include <vector>


const std::string DATA_LOC = "../data/";
const int PADDING = 1;
const int NR = 1021;
const int NC = 1344;
const int NR_P = NR + PADDING * 2;
const int NC_P = NC + PADDING * 2;


/* Convert 2D-indexing to 1D index */
int from_2D_to_1D(int x, int y);


/* Compute distance between pixel i,j and pixel x,y */
void rgb_distance(dlib::array2d<dlib::rgb_pixel> &img, int i, int j, int x, int y, 
    int &red, int &green, int &blue);


/* For pixel i,j compute mean distance between it and its neighbours */ 
void compute_distance(dlib::array2d<dlib::rgb_pixel> &img, int i, int j, 
        dlib::array2d<dlib::rgb_pixel> &result, std::vector<int> &distance_array); 


/* Add padding to image - size of padding specified under PADDING */
dlib::array2d<dlib::rgb_pixel> add_padding(dlib::array2d<dlib::rgb_pixel> &img);


/* Process single image - calculate distance between its pixels */
void process_image(const std::string img_name, dlib::array2d<dlib::rgb_pixel> &result, 
        std::vector<int> &distance_array, int index, int x_size);


/* Get images from directory specified under DATA_LOC */
bool get_images(std::vector<std::string> &filenames);



#endif /* IMG_TRANSFORM_H */
