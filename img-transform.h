#ifndef IMG_TRANSFORM_H
#define IMG_TRANSFORM_H

#include <sys/types.h>
#include <dirent.h>
#include <dlib/image_io.h>
#include <dlib/array2d.h>
#include <vector>


const int PADDING = 1;
const int NR = 1021;
const int NC = 1344;
const int NR_P = NR + PADDING * 2;
const int NC_P = NC + PADDING * 2;
const int RGB_RANGE = 255;


/* Convert 2D-indexing to 1D index */
int from_2D_to_1D(int x, int y);


/* Scale values to value from range (0, 255) */
int scale_to_255(int v, int min_value, int max_value);


/* Compute distance between pixel i,j and pixel x,y */
void rgb_distance(dlib::array2d<dlib::rgb_pixel> &img, 
        int i, int j, int x, int y, 
        int &red, int &green, int &blue);


void compare_distance(dlib::array2d<dlib::rgb_pixel> &img, int i, int j, 
        int dist, dlib::array2d<dlib::rgb_pixel> &result, std::vector<int> &distance_array, 
        std::vector<int> &picture_ids, int picture_id);

/* For pixel i,j compute mean distance between it and its neighbours */ 
void compute_distance(dlib::array2d<dlib::rgb_pixel> &img, 
        int i, int j, dlib::array2d<dlib::rgb_pixel> &result, 
        std::vector<int> &distance_array, std::vector<int> &picture_ids); 


/* Add padding to image - size of padding specified under PADDING */
dlib::array2d<dlib::rgb_pixel> add_padding(dlib::array2d<dlib::rgb_pixel> &img);


/* Process single image - calculate distance between its pixels */
void process_image(const std::string img_name, 
        dlib::array2d<dlib::rgb_pixel> &result, 
        std::vector<int> &distance_array, std::vector<int> &picture_ids,
        int picture_id, int x_size);


/* Get images from directory specified under DATA_LOC */
bool get_images(std::vector<std::string> &filenames, std::string &data_location);


/* Draw depth map from pictutes used for first image */
void draw_depth_map(dlib::array2d<dlib::rgb_pixel> &depth_map, std::vector<int> &picture_ids, int no_images);

#endif /* IMG_TRANSFORM_H */
