/*************************************************************************************/
/*!
    \file     enregistreur.cpp
    \author   Philippe SIMIER (Touchard Wahington le Mans)

    \brief    Programme pour enregistrer une vidéo dans un fichier MPEG
    \detail   Ce programme ouvre la camera puis enregistre la video dans un fichier.


    \compilation
	      g++ $(pkg-config --libs --cflags opencv) -o enregistreur  enregistreur.cpp
	      g++ -ggdb enregistreur.cpp -o enregistreur `pkg-config --cflags --libs opencv`

    \version    1.0 - First release
*/
/**************************************************************************************/

#include <iostream>
#include <string>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int main(int argc,char ** argv)
{
  Mat image, image_inv;
  double largeur,hauteur, fps;
  string nomFichier;
  string extension =".avi";

  VideoCapture capture(0);
  if (!capture.isOpened()) {
    cerr << "ERREUR: Impossible d'ouvrir la camera" << endl;
    return -1;
  }

  largeur = capture.get(CAP_PROP_FRAME_WIDTH);
  hauteur = capture.get(CAP_PROP_FRAME_HEIGHT);
  fps	= capture.get(CAP_PROP_FPS);
  Size taille( (int)largeur, (int) hauteur);
  VideoWriter writer;
  if (argc == 1){
  	writer.open( "input.avi", CV_FOURCC('M','J','P','G'), fps, taille);

  }
  else{
	nomFichier = argv[1] + extension;
        writer.open( nomFichier, CV_FOURCC('M','J','P','G'), fps, taille);
  }

  cout << "Taille image : " << largeur << " x " << hauteur << endl;

  cout << "Démarrage de la capture, appuyer sur une touche du clavier pour quitter" << endl;
  do{
    capture >> image;
    if (image.empty()) {
        cerr << "ERREUR: Impossible de capturer une image" << endl;
        return -1;
    }

    imshow("live", image);
    writer << image;
  }
  while(waitKey(5) !='x');

  cout << "Fermeture de la  camera" << endl;
  capture.release();
  destroyAllWindows();
  cout << "bye!" <<endl;
  return 0;
}
