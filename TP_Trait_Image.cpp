//Include de OpenCV
#include <opencv2/core.hpp> // noyaux de OpenCV
#include <opencv2/imgcodecs.hpp> //images
#include <opencv2/imgproc.hpp> //traitement d'images
#include <opencv2/highgui.hpp> //gui

//Include C++
#include <iostream>
using namespace cv;


//Image,ligne,colone,couleur
void setPixel(Mat&, int, int, uchar);
void setImgInGray(Mat&, Mat&);
void setLigneHorizontal(Mat&, int, int, int);
void setLigneVertical(Mat&, int, int, int);

//CONSTANTE
const unsigned char BLANC = 255, NOIR = 0;


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
    
    //Mettre l'image en noir
    setImgInGray(imgOrig, imgGray);
    for (int i = 0; i < imgGray.rows; i++)
        for (int j = 0; j < imgGray.cols; j++)
            setPixel(imgGray, i, j, NOIR);        
    
    int lg = 200, indexLg = 0,
        la = 150, indexLa = 0,
        dia = (200) ^ 2 + (100) ^ 2;
    
    // Sans iterator
    int cote = 150, i = 0, j = 0;
    setLigneHorizontal(imgGray, 45, 45, cote);
    setLigneVertical(imgGray, 45, 45, cote);
    setLigneHorizontal(imgGray, 195, 45, cote);
    setLigneVertical(imgGray, 45, 195, cote);
    
    int posPixelLigne = 45, posPixelCol = 45;

    while (posPixelLigne <= 195 && posPixelCol <= 195)
    {
        setPixel(imgGray, posPixelLigne, posPixelCol, BLANC);
        posPixelLigne++; posPixelCol++;
    }
    posPixelLigne = 45;
    posPixelCol = 195;
    while (posPixelLigne <= 195 && posPixelCol >= 45)
    {
        setPixel(imgGray, posPixelLigne, posPixelCol, BLANC);
        posPixelLigne++; posPixelCol--;
    }
      




    //imshow("Image Origine ", imgOrig);
    imshow("Image Gris� ", imgGray);

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
    cvtColor(imgOrig, imgGray, COLOR_RGB2GRAY); //transformer l'image en gris�
    //imshow("Image Gris� ", imgGray);
}

void setLigneHorizontal(Mat& img,int posLigne,int posCol, int taille)
{
    for (int c = posCol; c <= (taille+posCol); c++)
    {
        setPixel(img, posLigne, c, BLANC);
    }
}

void setLigneVertical(Mat& img, int posLigne, int posColone, int taille)
{
    for (int r = posLigne; r <= (taille+posLigne); r++)
    {
        setPixel(img, r, posColone, BLANC);
    }
}

void setPixel(Mat &image, int ligne, int col, uchar couleur)
{
    CV_Assert(image.channels() == 1);//si l'image est � un seul channel (1 octet)
    image.at<uchar>(ligne, col) = couleur;
}
