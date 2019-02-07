/*************************************************************************************/
/*!
    \file     testCanny.cpp
    \author   Philippe SIMIER (Touchard Wahington le Mans) <philaure@wanadoo.fr>

    \brief    Programme pour renforcer les contours avec le filtre de Canny
    \detail   Ce programme ouvre la camera puis affiche l'image obtenue en
              appliquant le traitement Canny edge detector.
	      Le filtre de Canny (ou détecteur de Canny) est utilisé pour la
              détection des contours.
              L'algorithme a été conçu par John Canny en 1986

    \compilation raspberry
	      g++ $(pkg-config --libs --cflags opencv) -o Canny  Canny.cpp
    \compilation linux mint
              g++  Canny.cpp -o Canny `pkg-config --cflags --libs opencv`

    \version    1.0 - First release
*/
/**************************************************************************************/

#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

void showControle(int *seuilA, int *seuilB){
    //Creation d'un trackbar dans la fenêtre "Control"
    namedWindow("Canny",1);
    cvCreateTrackbar("SeuilA", "Canny", seuilA, 255);
    cvCreateTrackbar("SeuilB", "Canny", seuilB, 255);
}


int main(int argc,char ** argv)
{
    Mat image, image_RGB, image_gray, image_CNY;
    int seuilA = 17;
    int seuilB = 43;
    double largeur,hauteur;

    showControle(&seuilA, &seuilB);


    VideoCapture cap(0);
    if (!cap.isOpened()) {
        cerr << "ERREUR: Impossible d'ouvrir la camera" << endl;
    	return -1;
    }

    largeur = cap.get(CV_CAP_PROP_FRAME_WIDTH);
    hauteur = cap.get(CV_CAP_PROP_FRAME_HEIGHT);
    cout << "Taille image : " << largeur << " x " << hauteur << endl;

    cout << "Démarrage de la capture, appuyer sur une touche echap pour quitter" << endl;

    do{
      cap >> image;
      if (image.empty()) {
          cerr << "ERREUR: Impossible de capturer une image" << endl;
          return -1;
      }

      cvtColor( image, image_gray, CV_RGB2GRAY);
      blur( image_gray, image_gray, Size(3,3) );

      Canny( image_gray, image_CNY, seuilA, seuilB, 3, true );
      imshow("Canny", image_CNY);

    }
    while(waitKey(1) != 27);

    cout << "Fermeture de la  camera" << endl;
    cap.release();
    destroyAllWindows();
    cout << "bye!" <<endl;
    return 0;
}
