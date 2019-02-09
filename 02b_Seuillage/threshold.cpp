/*************************************************************************************/
/*!
    \file     threshold.cpp
    \author   Philippe SIMIER (Touchard Wahington le Mans)

    \brief    Programme pour tester l'installation d'OpenCV 3 avec la raspiCam
    \detail   Ce programme ouvre la camera puis affiche l'image obtenue après traitement
              avec la fonction threshold

    \compilation
	      g++ -ggdb threshold.cpp -o threshold `pkg-config --cflags --libs opencv`

    \version    1.0 - First release
*/
/**************************************************************************************/

#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>

using namespace cv;
using namespace std;

int main(int argc,char ** argv)
{
    Mat image, image1;
    double largeur,hauteur;
    int seuil = 100;
    int max = 255;
    VideoCapture cap;
    string titre;

    if (argc == 1) {
  	cap.open(0); // ouverture de la première caméra
	titre = "Camera Live";
    }
    else{
	cap.open(argv[1]); // sinon ouverture du fichier video
	titre = argv[1];
    }

    if (!cap.isOpened()) {
        cerr << "ERREUR: Impossible d'ouvrir le flux vidéo" << endl;
        return -1;
    }

    largeur = cap.get(CV_CAP_PROP_FRAME_WIDTH);
    hauteur = cap.get(CV_CAP_PROP_FRAME_HEIGHT);
    cout << "Taille image : " << largeur << " x " << hauteur << endl;

    cout << "Ouverture du flux vidéo, appuyer sur q pour quitter" << endl;
    namedWindow("threshold",1);

    //Create trackbar to change seuil
    createTrackbar("seuil", "threshold", &seuil, 255);

    //Create trackbar to change max
    createTrackbar("max", "threshold", &max, 255);

    bool vide = true;
    do{
    cap >> image;
    if (!(vide = image.empty()))
        {
    	cvtColor( image, image1, CV_RGB2GRAY);
    	threshold(image1, image, (double)seuil,(double)max, THRESH_BINARY_INV);
    	imshow("threshold", image);
        }

   }
   while(waitKey(1) !='q' && !vide);

   cout << "Fermeture du flux vidéo" << endl;
   cap.release();
   cout << "bye!" <<endl;
   return 0;
}
