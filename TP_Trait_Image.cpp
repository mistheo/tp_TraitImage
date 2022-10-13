//Include de OpenCV
#include <opencv2/core.hpp> // noyaux de OpenCV
#include <opencv2/imgcodecs.hpp> //images
#include <opencv2/imgproc.hpp> //traitement d'images
#include <opencv2/highgui.hpp> //gui

//Include C++
#include <iostream>
using namespace cv;

void setPixel(Mat&, int, int, uchar);
void setImgInGray(Mat&, Mat&);
const uchar BLANC = 255, NOIRE = 0;


int main()
{  
    std::string image_path = samples::findFile("starry_night.jpg");
    Mat imgOrig = imread(image_path, IMREAD_COLOR);
    Mat imgGray = imread("starr_night_gray.jpg", IMREAD_GRAYSCALE);

    if (imgOrig.empty())//Si le fichier n'existe pas
    {
        std::cout << "Could not read the image: " << image_path << std::endl;
        return 1;
    }
    
    setImgInGray(imgOrig, imgGray);
    imshow("Image Origine ", imgOrig);
    imshow("Image Grisé ", imgGray);

    if (waitKey(0) == 's')
    {
        imwrite("starry_night.jpg", imgOrig);
    }
    return 0;

}

void setImgInGray(Mat& imgOrig,Mat& imgGray)
{
    //imshow("Image Origine ", imgOrig);
    imgGray *= 1. / 255;
    cvtColor(imgOrig, imgGray, COLOR_RGB2GRAY); //transformer l'image en grisé
    //imshow("Image Grisé ", imgGray);
}



void setPixel(Mat& image, int i, int j , uchar couleur)
{
    // accept only char type matrices
    CV_Assert(image.depth() == CV_8U);
    CV_Assert(image.channels() == 1);
    const int channels = image.channels();
    if(channels==1) image.at<uchar>(i, j) = couleur;
}
