#include <opencv4/opencv2/opencv.hpp>
#include <opencv4/opencv2/videoio.hpp>

#include <ctime>
#include <iostream>
#include <iterator>
#include <locale>

using namespace cv;

static VideoCapture cap;

void camera_init() { cap = VideoCapture(0); };

void camera_save_image(std::string filename)
{
    std::cout << "filename: " << filename << std::endl;
    Mat image;
    cap >> image;
    if (image.empty())
    {
        std::cout << "ERROR! CAMERA IMAGE IS EMPTY!" << std::endl;
        return;
    }

    imwrite(filename + ".png", image);
};

void camera_stop()
{
    cap.release();
};
