#include <iostream>
#include <sys/types.h>
#include <dirent.h>
#include <dlib/image_io.h>
#include <dlib/array2d.h>

using namespace dlib;

const int NR = 1021;
const int NC = 1344;

inline void rgb_distance(array2d<rgb_pixel> &img, int i, int j, int x, int y, int *red, int *green, int *blue) {
    *red += img[i][j].red - img[x][y].red;
    *green += img[i][j].green - img[x][y].green,
    *blue += img[i][j].blue - img[x][y].blue;
}

void compute_distance(array2d<rgb_pixel> &img, int i, int j, int ***d) {
    int c = 0; 
    int red = 0, green = 0, blue = 0;
    if (i > 0 && j > 0) {
        rgb_distance(img, i, j, i - 1, j - 1, &red, &green, &blue);
        ++c;
    }
    if (i > 0) {
        rgb_distance(img, i, j, i - 1, j, &red, &green, &blue);
        ++c;
    }
    if (j > 0) {
        rgb_distance(img, i, j, i, j - 1, &red, &green, &blue);
        ++c;
    }
    if (i < img.nr() - 1 && j < img.nc() - 1) {
        rgb_distance(img, i, j, i + 1, j + 1, &red, &green, &blue);
        ++c;
    }
    if (i < img.nr() - 1) {
        rgb_distance(img, i, j, i + 1, j, &red, &green, &blue);
        ++c;
    }
    if (j < img.nc() - 1) {
        rgb_distance(img, i, j, i, j + 1, &red, &green, &blue);
        ++c;
    }
    red /= c * 1.0;
    green /= c * 1.0;
    blue /= c * 1.0;
    if (d[i][j][0] < red) {
        d[i][j][0] = red;
        d[i][j][3] = img[i][j].red;
    }
    if (d[i][j][1] < green) {
        d[i][j][1] = green;
        d[i][j][4] = img[i][j].green;
    }
    if (d[i][j][2] < blue) {
        d[i][j][2] = blue;
        d[i][j][5] = img[i][j].blue;
    }
}

void process_image(const std::string img_name, int ***d) {

    array2d<rgb_pixel> img;
    load_png(img, img_name);

    for(int i = 0; i < img.nr(); ++i) {
        for(int j = 0; j < img.nc(); ++j){
            compute_distance(img, i, j, d);
        }
    }

}

int main(void) {
    
    auto result = array2d<rgb_pixel>(NR, NC);
    
    int ***d = new int **[NR];
    
    for (int i = 0; i < NR; ++i) {
        d[i] = new int *[NC];
        for(int j = 0; j < NC; ++j) {
            d[i][j] = new int[6]();
        }
    }

    std::vector<std::string> filenames; 
    DIR *dirp = opendir("data");
    struct dirent *dp;
    while ((dp = readdir(dirp)) != NULL) {
        std::string name = "data/";
        name += dp->d_name;
        if (dp->d_name != "result.png" && name.find(".png") != std::string::npos) filenames.push_back(name); 
    }
    closedir(dirp);

    for (auto n : filenames) {
        process_image(n, d);
    }

    for(int i = 0; i < NR; ++i) {
        for(int j = 0; j < NC; ++j){
            result[i][j].red = d[i][j][3];
            result[i][j].green = d[i][j][4];
            result[i][j].blue = d[i][j][5];
        }
    }

    save_png(result, "r.png");

    for (int i = 0; i < NR; ++i) {
        for(int j = 0; j < NC; ++j) {
            delete[] d[i][j];
        }
        delete[] d[i];
    }
    delete[] d;
}
