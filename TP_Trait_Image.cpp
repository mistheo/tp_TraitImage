#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

#include <iostream>
using namespace cv;


int main()
{
    std::string image_path = samples::findFile("starry_night.jpg");
    Mat img = imread(image_path, IMREAD_COLOR);
    Mat imgGray = imread("starr_night_gray.jpg", IMREAD_GRAYSCALE);


    if (img.empty())
    {
        std::cout << "Could not read the image: " << image_path << std::endl;
        return 1;
    }
    imshow("Image Origine", img);
 

    imgGray *= 1. / 255;
    cvtColor(img, imgGray, COLOR_RGB2GRAY);

    imshow("Image Grisé", imgGray);
    int k = waitKey(0); // Wait for a keystroke in the window
    if (k == 's')
    {
        imwrite("starry_night.jpg", img);
    }
    return 0;
}