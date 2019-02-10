/*************************************************************************************/
/*!
    \file     lecture.cpp
    \author   Philippe SIMIER (Touchard Wahington le Mans)
    \brief    Programme pédagogique pour montrer imread imwrite imshow
    \compilation
              g++ -ggdb lecture.cpp -o lecture `pkg-config --cflags --libs opencv`
    \version    1.0 - First release
*/
/**************************************************************************************/


#include <iostream>

#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <vector>

using namespace cv;
using namespace std;

int main(int argc,char ** argv)
{

    // lecture d'une image
    Mat image = imread("Penguins.jpg");

    // Affichage d'une image
    imshow("maFenetre", image);
    waitKey(0);

    // Ecriture d'une image paramètres par défaut
    bool isSuccess = imwrite("monImage.jpg", image);

    if (isSuccess == false)
    {
        cout << "Erreur lors de l'enregistrement de l'image" << endl;
        return -1;
    }

    // Ecriture de l'image en jpg avec un parametre de qualité fixé à 50
    vector<int>  compression_params_jpg ;
    compression_params_jpg . push_back ( CV_IMWRITE_JPEG_QUALITY );
    compression_params_jpg . push_back ( 50 );


    isSuccess = imwrite("monImage2.jpg", image, compression_params_jpg);

    if (isSuccess == false)
    {
        cout << "Erreur lors de l'enregistrement de l'image" << endl;
        return -1;
    }

    // Ecriture de l'image en png
    vector<int> compression;
    compression.push_back ( CV_IMWRITE_PNG_COMPRESSION );
    compression.push_back(9); // 0 (sans compression) -> 9 (compression max)

    isSuccess = imwrite("monImage3.png", image, compression);

    if (isSuccess == false)
    {
        cout << "Erreur lors de l'enregistrement de l'image" << endl;
        return -1;
    }


    return 0;
}
