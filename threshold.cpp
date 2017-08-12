/*************************************************************************************/
/*!
    \file     threshold.cpp
    \author   Philippe SIMIER (Touchard Wahington le Mans)

    \brief    Programme pour tester l'installation d'OpenCV 3 avec la raspiCam
    \detail   Ce programme ouvre la camera puis affiche l'image obtenue avec threshold

    \compilation
	      g++ $(pkg-config --libs --cflags opencv) -o threshold  threshold.cpp

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
  int max = 100;

  VideoCapture cap(0);
  if (!cap.isOpened()) {
    cerr << "ERREUR: Impossible d'ouvrir la camera" << endl;
    return -1;
  }

  largeur = cap.get(CV_CAP_PROP_FRAME_WIDTH);
  hauteur = cap.get(CV_CAP_PROP_FRAME_HEIGHT);
  cout << "Taille image : " << largeur << " x " << hauteur << endl;

  cout << "Démarrage de la capture, appuyer sur une touche du clavier pour quitter" << endl;
  namedWindow("threshold",1);

  //Create trackbar to change seuil
     createTrackbar("seuil", "threshold", &seuil, 255);

  //Create trackbar to change max
     createTrackbar("max", "threshold", &max, 255);


  do{
    cap >> image;
    if (image.empty()) {
        cerr << "ERREUR: Impossible de capturer une image" << endl;
        return -1;
    }

    flip( image, image1, -1); // mirroir horizontal
    cvtColor( image1, image, CV_RGB2GRAY);
    threshold(image, image1, (double)seuil,(double)max, THRESH_BINARY_INV);
    imshow("threshold", image1);
  }
  while(waitKey(25) !='x');

  cout << "Fermeture de la  camera" << endl;
  cap.release();
  destroyAllWindows();
  cout << "bye!" <<endl;
  return 0;
}
