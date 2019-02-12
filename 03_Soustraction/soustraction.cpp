/************************************************************************************/
/*!
    \file     soustraction.cpp
    \author   Philippe SIMIER (Touchard Wahington le Mans)

    \brief    Programme pour tester la soustraction d'arriere plan
    \detail   Cette démonstration vous permet de tester la fonction de soustraction d'arrière-plan
              incluse dans OpenCV. La soustraction d'arrière-plan peut être utile pour localiser
              des objets en mouvements ou ponctuels sur un arrière-plan fixe.
              C'est très simple : une caméra capture une frame et la compare avec la précédente
              qu'elle a mis en mémoire.  Si la différence entre ces deux images est supérieure
              à un certain seuil, le programme considère qu'il y a eu mouvement,
              et déclenche un actione particulière.
              OpenCV propose une fonction CountNonZero qui permet de calculer le nombre de pixels
              non noirs sur une image. Le nombre de pixels noirs correspond simplement à la résolution
              en pixels de l'image - le nombre de pixels non noirs !

    \compilation
	      g++ soustraction.cpp -o  soustraction `pkg-config --libs --cflags opencv`

    \version    1.0 - First release
*/
/*************************************************************************************/
#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>

using namespace cv;
using namespace std;


void showControle(int *seuil, int *nb){
  //Create trackbars in "Control" window
  namedWindow("Control",1);
  cvCreateTrackbar("Seuil", "Control", seuil, 255);
  cvCreateTrackbar("Nb", "Control", nb, 10000);
}


int main(int argc,char ** argv)
{

    Mat image, image1, image2, imageDiff;
    double largeur,hauteur;
    double fps;
    int seuilA = 20;    // seuil pour threshold
    int nbMax  = 3500;  // Nb de pixels ayant variés entre deux images consécutives
    showControle(&seuilA, &nbMax);
    int nb;

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

    cout << "Ouverture du flux vidéo, appuyer sur la touche echap du clavier pour quitter" << endl;

    // Lecture de la première image
    cap >> image;
    if (image.empty()) {
        cerr << "ERREUR: Impossible d'ouvrir le flux vidéo" << endl;
        return -1;
    }
    cvtColor( image, image1, CV_RGB2GRAY);

    bool vide = true;
    do {

        cap >> image;
        if (!(vide = image.empty()))
            cvtColor( image, image2, CV_RGB2GRAY);
            absdiff(image1, image2, imageDiff);// Absolute differences between the 2 images
            threshold(imageDiff, imageDiff, seuilA, 255, CV_THRESH_BINARY); // set threshold to ignore small differences you can also use inrange function
            imshow("thershold", imageDiff);
            nb = countNonZero(imageDiff == 255); // comptage des pixels
            if (nb > nbMax){
               putText(image, "Mouvement en cours!", Point(20, 20), FONT_HERSHEY_PLAIN, 1.0, CV_RGB(255,255,255), 2.0);
            }
            imshow("Live", image); // affichage de l'image dans une fenêtre pour contrôle
            image2.copyTo(image1);
        }
    while(waitKey(1) != 27 && !vide);

    cout << "Fermeture du flux vidéo" << endl;
    cap.release();
    cout << "bye!" <<endl;
    return 0;
}
