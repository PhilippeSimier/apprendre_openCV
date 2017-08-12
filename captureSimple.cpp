/************************************************************************************/
/*!
    \file     captureSimple.cpp
    \author   Philippe SIMIER (Touchard Wahington le Mans)

    \brief    Programme pour tester l'installation d'OpenCV 3 avec la raspiCam
    \detail   Ce programme ouvre la camera puis affiche l'image dans une fenêtre
              la fonction flip() effectue une transformation (effet miroir horizontal)
    \compilation
	      g++ $(pkg-config --libs --cflags opencv) -o captureSimple captureSimple.cpp

    \version    1.0 - First release
*/
/*************************************************************************************/
#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>

using namespace cv;
using namespace std;

int main(int argc,char ** argv)
{

  Mat image, image1;
  double largeur,hauteur;
  double fps;

  VideoCapture cap(0);
  if (!cap.isOpened()) {
    cerr << "ERREUR: Impossible d'ouvrir la camera" << endl;
    return -1;
  }

  largeur = cap.get(CAP_PROP_FRAME_WIDTH);
  hauteur = cap.get(CAP_PROP_FRAME_HEIGHT);
  fps     = cap.get(CAP_PROP_FPS);


  cout << "Taille image : " << largeur << " x " << hauteur << endl;
  cout << "Frame rate   : " << fps << " images par seconde" << endl;

  cout << "démarrage de la capture, appuyer sur la touche x du clavier pour quitter" << endl;

  do {
    cap >> image;
    if (image.empty()) {
        cerr << "ERREUR: Impossible de capturer une image" << endl;
        return -1;
    }
    flip(image, image1,-1); // mirroir horizontal
    imshow("Live", image1); // affichage de l'image dans une fenêtre
  }
  while(waitKey(5) !='x');

  cout << "Fermeture de la camera" << endl;
  cap.release();
  destroyAllWindows();
  cout << "bye!" <<endl;
  return 0;
}
