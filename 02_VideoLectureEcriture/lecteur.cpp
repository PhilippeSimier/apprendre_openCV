/************************************************************************************/
/*!
    \file     lecteur.cpp
    \author   Philippe SIMIER (Touchard Wahington le Mans) <philippe.simier@ac-nantes.fr>

    \brief    Programme pour lire et afficher un flux vidéo soit à partir d'un fichier ou d'une caméra
    \detail   Ce programme ouvre le flux vidéo issu d'une camera ou d'un fichier
	      puis l'affiche dans une fenêtre
              pour ouvrir le flux vidéo de la caméra le driver Video4Linux doit être chargé
	      pour ce faire utiliser la commande:	sudo modprobe bcm2835-v4l2
	      Vous pouvez également ajouter ce module à la liste des modules chargés au démarrage dans
	      /etc/modules-load.d/modules.conf


    \compilation linux
              g++ -ggdb lecteur.cpp -o lecteur `pkg-config --cflags --libs opencv4`

    \version    2.0 - Second release for opencv4

    \test	./lecteur chaplin.mp4
		./lecteur
*/
/*************************************************************************************/
#include <iostream>
#include <string>  // la biblio string de std

#include <opencv2/highgui/highgui.hpp>
#include <opencv2/videoio.hpp>

using namespace cv;
using namespace std;

int main(int argc,char ** argv)
{

    Mat image;
    double largeur,hauteur;
    VideoCapture cap;
    string titre;
    int fps;

    if (argc == 1) {
  	cap.open(0); // ouverture de la première caméra
	titre = "Camera Live";
    }
    else{
	cap.open(argv[1]);
	titre = argv[1];
    }

    if (!cap.isOpened()) {
        cerr << "ERREUR: Impossible d'ouvrir le flux vidéo" << endl;
        return -1;
    }

    largeur = cap.get(cv::CAP_PROP_FRAME_WIDTH);
    hauteur = cap.get(cv::CAP_PROP_FRAME_HEIGHT);
    fps     = cap.get(cv::CAP_PROP_FPS);

    cout << "Frame rate   : " << fps << " images par seconde" << endl;
    cout << "Taille image : " << largeur << " x " << hauteur << endl;

    cout << "démarrage de la lecture, appuyer sur la touche Echap du clavier pour quitter" << endl;
    bool vide = true;
    do {
        cap >> image;

        if (!(vide = image.empty()))
            imshow(titre, image); // affichage de l'image dans la fenêtre
    }
    while(waitKey(1000/fps) != 27 && !vide);

    cout << "Fermeture du flux vidéo" << endl;
    cap.release();
    //destroyAllWindows();
    cout << "bye!" <<endl;
    return 0;
}
