/*************************************************************************************/
/*!
    \file     captureNoirEtBlanc.cpp
    \author   Philippe SIMIER (Touchard Wahington le Mans)

    \brief    Programme pour tester l'installation d'OpenCV 3 avec la raspiCam
    \detail   Ce programme ouvre la camera puis affiche l'image en noir et blanc dans une fenêtre
              la fonction flip() effectue une transformation (effet miroir horizontal)
	      la fonction cvtColor() effectue la transformation en noir et blanc
    \compilation
	      g++ $(pkg-config --libs --cflags opencv) -Wall -o captureNoirEtBlanc  captureNoirEtBlanc.cpp

    \version    1.0 - First release
*/
/**************************************************************************************/

#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>

using namespace cv;
using namespace std;

int main(int argc, char ** argv)
{
  Mat image, image1,framebw;
  double largeur,hauteur;

  VideoCapture cap(0);
  if (!cap.isOpened()) {
    cerr << "ERREUR: Impossible d'ouvrir la camera" << endl;
    return -1;
  }

  largeur = cap.get(CV_CAP_PROP_FRAME_WIDTH);
  hauteur = cap.get(CV_CAP_PROP_FRAME_HEIGHT);
  cout << "Taille image : " << largeur << " x " << hauteur << endl;

  cout << "Démarrage de la capture, appuyer sur la touche x du clavier pour quitter" << endl;

  do {
    cap >> image;
    if (image.empty()) {
        cerr << "ERREUR: Impossible de capturer une image" << endl;
        return -1;
    }
    flip( image, image1, -1); // mirroir horizontal
    cvtColor( image1, image, CV_RGB2GRAY);
    imshow("Live", image);
  }
  while(waitKey(5) !='x');

  cout << "Fermeture de la  camera" << endl;
  cap.release();
  destroyAllWindows();
  cout << "bye!" <<endl;
  return 0;
}
