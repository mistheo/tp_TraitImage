#include "CTraitementImage.h"

void CTraitementImage::setPixel(Mat& img, int ligne, int col, uchar couleur)
{
    uchar* ptr = img.ptr();
    *(ptr + (ligne * img.cols + col)) = couleur;

}

uchar CTraitementImage::getPixel(Mat& img, int ligne, int col)
{
    return img.at<uchar>(ligne, col);
}

CTraitementImage::CTraitementImage()
{
}

CTraitementImage::~CTraitementImage()
{
}

Mat CTraitementImage::binarisation(Mat&imgModif, int valDefine)
{
    Mat imgRetour = imgModif.clone();
    cvtColor(imgModif, imgRetour, COLOR_RGB2GRAY); //transformer l'image en grisé

    for (int i = 0; i < imgRetour.rows; i++)
    {
        for (int j = 0; j < imgRetour.cols; j++)
        {
            if ((int)getPixel(imgRetour, i, j) < valDefine)
                setPixel(imgRetour, i, j, 0);//mettre en noir
            else
                setPixel(imgRetour, i, j, 255);//mettre en blanc
        }
    }

    return imgRetour;
}

Mat CTraitementImage::erosion(Mat& imgOrig)
{
    Mat imgRetour = imgOrig.clone();
    uchar myPixel = 0;
    int nbPixNoir = 0;
    int ligne = 0;
    int col = 0;

    //Parcours de l'image entiere
    for (int i = 1; i < imgOrig.rows-1; i++)//par ligne
    {
        for (int j = 1; j < imgOrig.cols-1; j++)//par colonne
        {

            //regarde les pixels autours du pixels actuels
            //1er ligne
            myPixel = getPixel(imgOrig, i - 1, j - 1);
            if (myPixel == 0)
                nbPixNoir++;
            myPixel = getPixel(imgOrig, i - 1, j);
            if (myPixel == 0) 
                nbPixNoir++;
            myPixel = getPixel(imgOrig, i - 1, j + 1);
            if (myPixel == 0) 
                nbPixNoir++;

            //2e ligne
            myPixel = getPixel(imgOrig, i, j - 1);
            if (myPixel == 0) 
                nbPixNoir++;            
            myPixel = getPixel(imgOrig, i, j);
            if (myPixel == 0) 
                nbPixNoir++;
            myPixel = getPixel(imgOrig, i, j + 1);
            if (myPixel == 0) 
                nbPixNoir++;

            //3e ligne
            myPixel = getPixel(imgOrig, i + 1, j - 1);
            if (myPixel == 0) 
                nbPixNoir++;
            myPixel = getPixel(imgOrig, i + 1, j);
            if (myPixel == 0) 
                nbPixNoir++;          
            myPixel = getPixel(imgOrig, i + 1, j + 1);
            if (myPixel == 0) 
                nbPixNoir++;

            //on compte les pixels
            if (nbPixNoir >= 4) 
                setPixel(imgRetour, i, j, 0);//majorité de noir : pixel noir
            else 
                setPixel(imgRetour, i, j, 255);
            
            nbPixNoir = 0;
        }
    }

    return imgRetour;
}
