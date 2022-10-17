//Include de OpenCV
#include <opencv2/core.hpp> // noyaux de OpenCV
#include <opencv2/imgcodecs.hpp> //images
#include <opencv2/imgproc.hpp> //traitement d'images
#include <opencv2/highgui.hpp> //gui

//Include C++
#include <iostream>
#include "CTraitementImage.h"
using namespace cv;

//Image,ligne,colone,couleur
void dessinCarre(Mat&);
void setPixel(Mat&, int, int, uchar);
void setPixelV2(Mat&, int, int, uchar);
void setPixelV3(Mat&, int, int, uchar);
uchar getPixel(Mat&, int, int);
void setLigneHorizontal(Mat&, int, int, int);
void setLigneVertical(Mat&, int, int, int);

//CONSTANTES
const unsigned char BLANC = 255, NOIR = 0;


int main()
{
    std::string image_path = "Images/Image4balles.png"; Mat imgOrig = imread(image_path, IMREAD_COLOR); 
    if (imgOrig.empty())//Si le fichier n'existe pas
    {
        std::cout << "Could not read the image: " << image_path << std::endl;
        return 1;
    }

    CTraitementImage traitImg;

    Mat imgBnW = traitImg.binarisation(imgOrig,128);
    Mat imgEros = traitImg.erosion(imgBnW);
    for (int l = 0; l < 100; l++)
        imgEros = traitImg.erosion(imgEros);

    imshow(image_path + " Origine ", imgOrig);
    imshow(image_path + " Binarisation ", imgBnW);
    imshow(image_path + " Erosion ", imgEros);
    if (waitKey(0) == 's')
    {
        imwrite(image_path, imgOrig);
    }

    return 0;
}

void dessinCarre(Mat& imgOrig)
{
    //dessiner un carr�
    int cote = 150;
    setLigneHorizontal(imgOrig, 45, 45, cote);
    setLigneVertical(imgOrig, 45, 45, cote);
    setLigneHorizontal(imgOrig, 195, 45, cote);
    setLigneVertical(imgOrig, 45, 195, cote);

    int posPixelLigne = 45, posPixelCol = 45;

    //diagonal haut gauche vers bas droite
    while (posPixelLigne <= 195 && posPixelCol <= 195)
    {
        //setPixel(imgGray, posPixelLigne, posPixelCol, BLANC);
        //setPixelV2(imgGray, posPixelLigne, posPixelCol, BLANC);
        setPixelV3(imgOrig, posPixelLigne, posPixelCol, BLANC);
        posPixelLigne++; posPixelCol++;
    }

    //diagonal haut droite vers bas gauche
    posPixelLigne = 45; posPixelCol = 195;
    while (posPixelLigne <= 195 && posPixelCol >= 45)
    {
        //setPixel(imgGray, posPixelLigne, posPixelCol, BLANC);
        //setPixelV2(imgGray, posPixelLigne, posPixelCol, BLANC);
        setPixelV3(imgOrig, posPixelLigne, posPixelCol, BLANC);
        posPixelLigne++; posPixelCol--;
    }
}
void setLigneHorizontal(Mat& img, int posLigne, int posCol, int taille)
{
    for (int c = posCol; c <= (taille + posCol); c++)
    {
        //setPixel(img, posLigne, c, BLANC);
        //setPixelV2(img, posLigne, c, BLANC);
        setPixelV3(img, posLigne, c, BLANC);
    }

}
void setLigneVertical(Mat& img, int posLigne, int posColone, int taille)
{
    for (int r = posLigne; r <= (taille + posLigne); r++)
    {
        //setPixel(img, r, posColone, BLANC);
        //setPixelV2(img, r, posColone, BLANC);
        setPixelV3(img, r, posColone, BLANC);
    }
}
void setPixel(Mat& image, int ligne, int col, uchar couleur)
{
    CV_Assert(image.channels() == 1);//si l'image est � un seul channel (1 octet)
    image.at<uchar>(ligne, col) = couleur;
}
uchar getPixel(Mat& img, int ligne, int col)
{
    return img.at<uchar>(ligne, col);
}
void setPixelV2(Mat& img, int ligne, int col, uchar couleur)
{
    MatIterator_<uchar> it;
    it = img.begin<uchar>();
    if (it + (ligne * img.cols + col) < img.end<uchar>())
        *(it + (ligne * img.cols + col)) = couleur;

}
void setPixelV3(Mat& img, int ligne, int col, uchar couleur)
{
    uchar* ptr = img.ptr();
    *(ptr + (ligne * img.cols + col)) = couleur;

}