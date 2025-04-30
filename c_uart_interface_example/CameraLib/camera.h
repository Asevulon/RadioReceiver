#include <opencv2/opencv.hpp>
#include <opencv2/videoio.hpp>

#include <ctime>
#include <iostream>
#include <iterator>
#include <locale>

using namespace cv;

static VideoCapture cap;

void camera_init();

void camera_save_image(std::string filename);

void camera_stop();