//Include de OpenCV
#include <opencv2/core.hpp> // noyaux de OpenCV
#include <opencv2/imgcodecs.hpp> //images
#include <opencv2/imgproc.hpp> //traitement d'images
#include <opencv2/highgui.hpp> //gui

//Include C++
#include <iostream>
#include "CTraitementImage.h"
using namespace cv;
//CONSTANTES
const unsigned char BLANC = 255, NOIR = 0;
//Image,ligne,colone,couleur
void dessinCarre(Mat&);
void setPixel(Mat&, int, int, uchar);
void setPixelV2(Mat&, int, int, uchar);
void setPixelV3(Mat&, int, int, uchar);
uchar getPixel(Mat&, int, int);
void setLigneHorizontal(Mat&, int, int, int);
void setLigneVertical(Mat&, int, int, int);

int main()
{
    CTraitementImage 
        traitImg;
    std::string 
        image_path = "Images/Image9Balles.png",
        video_path = "Images/Film1BisTpBalle.mp4";
    cv::Mat
        imgOrig = imread(image_path, IMREAD_COLOR),
        imgVid,
        imgBnW,
        imgEros,
        imgDila;
    cv::VideoCapture 
        myVid(video_path, CAP_FFMPEG);

    if (imgOrig.empty())//Si le fichier n'existe pas
    {
        std::cout << "-- Could not read the image: " << image_path << std::endl;
        return 1;
    }
    if (!myVid.isOpened())
    {
        std::cout << "-- Error opening video stream or file" << std::endl;
        return -1;
    }

    
    //int q = 0;
    //int i_img = 39;
    //int cptMoy = 0;
    //int cpt = 0;


    do
    {
        myVid >> imgVid; //une seule image de la vidéo dans une images;

        cv::imshow("Video", imgVid); waitKey(2);
        //imgBnW = traitImg.binarisation(imgOrig, 180);
        //
        //imgEros = traitImg.erosion(imgBnW);
        //for (int l = 0; l < 2; l++)
        //    imgEros = traitImg.erosion(imgEros);
        //
        //imgDila = traitImg.dilatation(imgEros);
        //for (int l = 0; l < 10; l++)
        //    imgDila = traitImg.dilatation(imgDila);
        //
        //std::cout << "------------- NOMBRE DE BALLES SUR L'IMAGE: " << traitImg.cptPixel(imgDila, BLANC)/5000 << std::endl;

    } while (waitKey(0)=='q');
    


    // en moyenne de 2200 à 3500 pixels / balles
    

    //imshow(image_path + " Origine ", imgOrig);
    //imshow(image_path + " Binarisation ", imgBnW);
    //imshow(image_path + " Erosion ", imgEros);
    //imshow(image_path + " Dilatation ", imgDila);


    //if (waitKey(0) == 's')
    //{
    //    imwrite(image_path, imgOrig);
    //}

    return 0;
}

void dessinCarre(Mat& imgOrig)
{
    //dessiner un carré
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
    CV_Assert(image.channels() == 1);//si l'image est à un seul channel (1 octet)
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