#pragma once

//Include OpenCV
#include <opencv2/core.hpp> // noyaux de OpenCV
#include <opencv2/imgcodecs.hpp> //images
#include <opencv2/imgproc.hpp> //traitement d'images
#include <opencv2/highgui.hpp> //gui

//Include C++
#include <iostream>
using namespace cv;

class CTraitementImage
{
	public:
		CTraitementImage();
		~CTraitementImage();
		
		void setPixel(Mat& img, int ligne, int col, uchar couleur);
		uchar getPixel(Mat& img, int ligne, int col);
		Mat binarisation(Mat&,int);
		Mat erosion(Mat&);

};

